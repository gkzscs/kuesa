/*
    main.cpp

    This file is part of Kuesa.

    Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Mauro Persano <mauro.persano@kdab.com>

    Licensees holding valid proprietary KDAB Kuesa licenses may use this file in
    accordance with the Kuesa Enterprise License Agreement provided with the Software in the
    LICENSE.KUESA.ENTERPRISE file.

    Contact info@kdab.com if any conditions of this licensing are not clear to you.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QResource>
#include <QDir>

#include "sampler.h"

#ifdef Q_OS_ANDROID
#include <QOpenGLContext>
#endif

namespace {

bool initializeAssetResources(const QVector<QString> &fileNames)
{
#ifdef Q_OS_MACOS
    QDir resourceDir(qApp->applicationDirPath() + QStringLiteral("/../Resources"));
#elif defined(Q_OS_IOS)
    QDir resourceDir(qApp->applicationDirPath() + QStringLiteral("/Library/Application Support"));
#else
    QDir resourceDir(qApp->applicationDirPath() + QStringLiteral("/resources"));
#endif
    bool b = true;
    for (const auto &fileName : fileNames) {
        auto f = resourceDir.path() + QDir::separator() + fileName;
        b &= QResource::registerResource(f);
        if (!b)
            qDebug() << "Failed to load assets from" << f;
    }
    return b;
}

} // namespace

int main(int argc, char *argv[])
{
    bool isES2 = false;
    {
        // Set OpenGL requirements
        QSurfaceFormat format = QSurfaceFormat::defaultFormat();
#ifndef QT_OPENGL_ES_2
        format.setVersion(4, 1);
        format.setProfile(QSurfaceFormat::CoreProfile);
        format.setSamples(4);
#else
#ifndef QT_OPENGL_ES_3
        isES2 = true;
#endif
        format.setVersion(3, 0);
        format.setProfile(QSurfaceFormat::NoProfile);
        format.setRenderableType(QSurfaceFormat::OpenGLES);
#endif
        QSurfaceFormat::setDefaultFormat(format);
    }

    QGuiApplication app(argc, argv);

    initializeAssetResources({ QStringLiteral("music-box.qrb") });
    initializeAssetResources({ QStringLiteral("envmap-pink-sunrise-16f.qrb") });
    qmlRegisterType<Sampler>("MusicBox", 1, 0, "Sampler");

    QQuickView view;
#ifdef KUESA_BUILD_ROOT
    view.engine()->addImportPath(QStringLiteral(KUESA_BUILD_ROOT "/qml"));
#endif
#ifdef Q_OS_IOS
    view.setFlags(view.flags() | Qt::MaximizeUsingFullscreenGeometryHint);
#endif


#ifdef Q_OS_ANDROID
    const QString assetsPrefix = QStringLiteral("assets:/");
    // Qt builds for android may not define QT_OPENGL_ES_3
    // Therefore we need a runtime check to see whether we can use ES 3.0 or not
    QOpenGLContext ctx;
    ctx.setFormat(QSurfaceFormat::defaultFormat());
    if (ctx.create()) {
        const QSurfaceFormat androidFormat = ctx.format();
        isES2 = (androidFormat.majorVersion() == 2);
    }
#else
    const QString assetsPrefix = QStringLiteral("qrc:/");
#endif
    view.engine()->rootContext()->setContextProperty(QStringLiteral("_isES2"), isES2);
    view.engine()->rootContext()->setContextProperty(QStringLiteral("_assetsPrefix"), assetsPrefix);

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.resize(960, 540);
    view.show();

    return app.exec();
}

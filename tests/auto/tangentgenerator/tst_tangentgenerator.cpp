/*
    tst_tangentgenerator.cpp

    This file is part of Kuesa.

    Copyright (C) 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: David Morgan <david.morgan@kdab.com>

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

#include <QtTest/QtTest>
#include <QDir>
#include <Kuesa/private/gltf2exporter_p.h>
#include <Kuesa/private/gltf2parser_p.h>
#include <Kuesa/private/meshparser_utils_p.h>

using namespace Kuesa;
using namespace GLTF2Import;

namespace {
static QDir setupTestFolder()
{
    QDir tmp(QStandardPaths::standardLocations(QStandardPaths::TempLocation)[0]);
    if (tmp.exists("kuesa-tangentgenerator-test")) {
        tmp.cd("kuesa-tangentgenerator-test");
        tmp.removeRecursively();
        tmp.cdUp();
    }
    tmp.mkdir("kuesa-tangentgenerator-test");
    tmp.cd("kuesa-tangentgenerator-test");
    tmp.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    return tmp;
}
} // namespace

class tst_TangentGenerator : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testTangentGeneration()
    {
        // GIVEN
        Kuesa::GLTF2Import::GLTF2Options options;
        GLTF2Context ctx;
        GLTF2Parser parser;
        parser.setContext(&ctx);
        parser.parse(QString(ASSETS "simple_cube_uv.gltf"));

        QVERIFY(ctx.meshesCount() == 1);
        auto mesh = ctx.mesh(0);

        QVERIFY(mesh.meshPrimitives.size() == 1);
        auto meshRenderer = mesh.meshPrimitives[0].primitiveRenderer;

        QVERIFY(Kuesa::GLTF2Import::MeshParserUtils::needsTangentAttribute(meshRenderer->geometry(),
                                                                           meshRenderer->primitiveType()));

        // WHEN
        QVERIFY(Kuesa::GLTF2Import::MeshParserUtils::generatePrecomputedTangentAttribute(meshRenderer, &ctx));

        // THEN
        QVERIFY(!Kuesa::GLTF2Import::MeshParserUtils::needsTangentAttribute(meshRenderer->geometry(),
                                                                            meshRenderer->primitiveType()));
    }

    void testTangentGenerationFileOutput()
    {
        // GIVEN
        auto tmp = setupTestFolder();
        auto gltfPath = tmp.absolutePath() + QDir::separator() + "simple_cube_uv.gltf";

        // WHEN
        {
            // GIVEN
            Kuesa::GLTF2Import::GLTF2Options options;
            GLTF2Context ctx;
            GLTF2Parser parser;
            parser.setContext(&ctx);
            parser.parse(QString(ASSETS "simple_cube_uv.gltf"));

            QVERIFY(ctx.meshesCount() == 1);
            auto mesh = ctx.mesh(0);

            QVERIFY(mesh.meshPrimitives.size() == 1);
            auto meshRenderer = mesh.meshPrimitives[0].primitiveRenderer;

            QVERIFY(Kuesa::GLTF2Import::MeshParserUtils::needsTangentAttribute(meshRenderer->geometry(),
                                                                               meshRenderer->primitiveType()));

            GLTF2Exporter::Export exported;

            // WHEN
            QVERIFY(Kuesa::GLTF2Import::MeshParserUtils::generatePrecomputedTangentAttribute(meshRenderer, &ctx));

            // THEN
            QVERIFY(!Kuesa::GLTF2Import::MeshParserUtils::needsTangentAttribute(meshRenderer->geometry(),
                                                                                meshRenderer->primitiveType()));

            GLTF2ExportConfiguration configuration;
            configuration.setMeshCompressionEnabled(false);
            configuration.setEmbedding(GLTF2ExportConfiguration::Embed::Keep);

            GLTF2Exporter exporter;
            exporter.setContext(&ctx);
            exporter.setConfiguration(configuration);
            exported = exporter.saveInFolder(QDir(ASSETS), tmp);

            QVERIFY(exporter.errors().empty());
            QVERIFY(exported.success());

            QFile file(gltfPath);
            QVERIFY(file.open(QIODevice::WriteOnly));
            QJsonDocument doc(exported.json());
            file.write(doc.toJson());
        }

        // THEN
        Kuesa::GLTF2Import::GLTF2Options options;
        GLTF2Parser parser;
        GLTF2Context ctx;
        parser.setContext(&ctx);
        parser.parse(gltfPath);

        QVERIFY(ctx.meshesCount() == 1);
        auto mesh = ctx.mesh(0);

        QVERIFY(mesh.meshPrimitives.size() == 1);
        auto meshRenderer = mesh.meshPrimitives[0].primitiveRenderer;

        QVERIFY(!Kuesa::GLTF2Import::MeshParserUtils::needsTangentAttribute(meshRenderer->geometry(),
                                                                            meshRenderer->primitiveType()));
    }
};

QTEST_APPLESS_MAIN(tst_TangentGenerator)

#include "tst_tangentgenerator.moc"

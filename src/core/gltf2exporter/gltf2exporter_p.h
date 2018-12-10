/*
    gltf2exporter_p.h

    This file is part of Kuesa.

    Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Jean-Michaël Celerier <jean-michael.celerier@kdab.com>

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

#ifndef KUESA_GLTF2EXPORTER_GLTF2EXPORTER_P_H
#define KUESA_GLTF2EXPORTER_GLTF2EXPORTER_P_H

//
//  NOTICE
//  ------
//
// We mean it: this file is not part of the public API and could be
// modified without notice
//

#include <QObject>
#include <QUrl>
#include <QDir>
#include <QJsonObject>
#include <QMap>
#include <Kuesa/kuesa_global.h>
#include <Kuesa/private/kuesa_global_p.h>

QT_BEGIN_NAMESPACE

namespace Kuesa {
class GLTF2Importer;
namespace GLTF2Import {
class GLTF2Context;
}
class SceneEntity;

class KUESA_PRIVATE_EXPORT GLTF2ExportConfiguration
{
public:
    enum MeshAttribute {
        Position,
        Normal,
        Color,
        TextureCoordinate,
        Generic
    };

    // O = slowest, 10 = fastest
    void setMeshEncodingSpeed(int speed);
    int meshEncodingSpeed() const;
    void setMeshDecodingSpeed(int speed);
    int meshDecodingSpeed() const;

    void setAttributeQuantizationLevel(MeshAttribute attribute, int level);
    int attributeQuantizationLevel(MeshAttribute) const;

    void setMeshCompressionEnabled(bool enabled);
    bool meshCompressionEnabled() const;

private:
    int m_encodingSpeed{};
    int m_decodingSpeed{};
    bool m_meshCompression{};
    QMap<MeshAttribute, int> m_quantization;
};

class KUESA_PRIVATE_EXPORT GLTF2Exporter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SceneEntity *scene READ scene WRITE setScene NOTIFY sceneChanged)

public:
    explicit GLTF2Exporter(QObject *parent = nullptr);

    SceneEntity *scene() const;
    QStringList errors() const;

    GLTF2ExportConfiguration configuration() const;
    void setConfiguration(const GLTF2ExportConfiguration &conf);

    void setContext(GLTF2Import::GLTF2Context *context);
    void setContextFromImporter(GLTF2Importer *importer);

Q_SIGNALS:
    void sceneChanged(SceneEntity *scene);

public Q_SLOTS:
    void setScene(SceneEntity *scene);

    QJsonObject saveInFolder(
            const QDir &sourceFolder,
            const QDir &targetFolder);

private:
    void copyURIs(const QDir &source, const QDir &target, const QJsonArray &array);

    GLTF2Import::GLTF2Context *m_context;
    SceneEntity *m_scene;

    GLTF2ExportConfiguration m_conf;
    QStringList m_errors;
};
} // namespace Kuesa
QT_END_NAMESPACE

#endif // KUESA_GLTF2EXPORTER_GLTF2EXPORTER_H


/*
    examplecustommaterialmaterial.h

    This file is part of Kuesa.

    Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Paul Lemire <paul.lemire@kdab.com>

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

#ifndef KUESA_EXAMPLECUSTOMMATERIALMATERIAL_H
#define KUESA_EXAMPLECUSTOMMATERIALMATERIAL_H

#include <Kuesa/GLTF2Material>
#include <Kuesa/kuesa_global.h>


QT_BEGIN_NAMESPACE

namespace Kuesa {

class ExampleCustomMaterialProperties;
class GLTF2MaterialProperties;

class ExampleCustomMaterialMaterial : public GLTF2Material
{
    Q_OBJECT
    Q_PROPERTY(Kuesa::ExampleCustomMaterialProperties *materialProperties READ materialProperties WRITE setMaterialProperties NOTIFY materialPropertiesChanged)

public:
    Q_INVOKABLE explicit ExampleCustomMaterialMaterial(Qt3DCore::QNode *parent = nullptr);
    ~ExampleCustomMaterialMaterial();

    ExampleCustomMaterialProperties *materialProperties() const;

public Q_SLOTS:
    void setMaterialProperties(Kuesa::ExampleCustomMaterialProperties *materialProperties);
    void setMaterialProperties(Kuesa::GLTF2MaterialProperties *materialProperties);

Q_SIGNALS:
    void materialPropertiesChanged(Kuesa::ExampleCustomMaterialProperties *materialProperties);

private:
    ExampleCustomMaterialProperties *m_materialProperties = nullptr;
    Qt3DRender::QParameter *m_shaderDataParameter;
};

} // namespace Kuesa

QT_END_NAMESPACE

#endif // KUESA_EXAMPLECUSTOMMATERIALMATERIAL_H

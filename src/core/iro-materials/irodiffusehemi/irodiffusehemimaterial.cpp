
/*
    irodiffusehemimaterial.cpp

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

#include "irodiffusehemimaterial.h"
#include "irodiffusehemiproperties.h"
#include "irodiffusehemishaderdata_p.h"
#include <Qt3DRender/qparameter.h>


QT_BEGIN_NAMESPACE

using namespace Qt3DRender;

namespace Kuesa {


/*!
    \class Kuesa::IroDiffuseHemiMaterial
    \inheaderfile Kuesa/IroDiffuseHemiMaterial
    \inherits Kuesa::GLTF2Material
    \inmodule Kuesa
    \since Kuesa 1.2

    \brief Kuesa::IroDiffuseHemiMaterial is a simple material in terms of rendering that relies on a 2d spherical environment map and a 2d diffuse map to render semi glossy like finishes like clear coated paint. It additionally shades the lower hemisphere by the color set in postHemiFilter.
*/

/*!
    \qmltype IroDiffuseHemiMaterial
    \instantiates Kuesa::IroDiffuseHemiMaterial
    \inqmlmodule Kuesa
    \since Kuesa 1.2

    \brief Kuesa::IroDiffuseHemiMaterial is a simple material in terms of rendering that relies on a 2d spherical environment map and a 2d diffuse map to render semi glossy like finishes like clear coated paint. It additionally shades the lower hemisphere by the color set in postHemiFilter.
*/

IroDiffuseHemiMaterial::IroDiffuseHemiMaterial(Qt3DCore::QNode *parent)
    : GLTF2Material(parent),
    m_shaderDataParameter(new Qt3DRender::QParameter(QStringLiteral("properties"), {}))
{
    addParameter(m_shaderDataParameter);
}

IroDiffuseHemiMaterial::~IroDiffuseHemiMaterial() = default;

/*!
    \property IroDiffuseHemiMaterial::materialProperties

    The properties defining the appearance of the material.

    \since Kuesa 1.2
 */

/*!
    \qmlproperty IroDiffuseHemiProperties IroDiffuseHemiMaterial::materialProperties

    The properties defining the appearance of the material.

    \since Kuesa 1.2
 */

Kuesa::IroDiffuseHemiProperties *IroDiffuseHemiMaterial::materialProperties() const
{
    return m_materialProperties;
}

void IroDiffuseHemiMaterial::setMaterialProperties(Kuesa::IroDiffuseHemiProperties *materialProperties)
{
    if (m_materialProperties != materialProperties) {
        m_materialProperties = materialProperties;
        emit materialPropertiesChanged(materialProperties);

        if (m_materialProperties) {
            m_shaderDataParameter->setValue(QVariant::fromValue(m_materialProperties->shaderData()));
            m_materialProperties->addClientMaterial(this);
        }
    }
}

void IroDiffuseHemiMaterial::setMaterialProperties(Kuesa::GLTF2MaterialProperties *materialProperties)
{
    setMaterialProperties(qobject_cast<Kuesa::IroDiffuseHemiProperties *>(materialProperties));
}

} // namespace Kuesa

QT_END_NAMESPACE

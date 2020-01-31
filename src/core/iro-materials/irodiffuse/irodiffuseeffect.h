
/*
    irodiffuseeffect.h

    This file is part of Kuesa.

    Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef KUESA_IRODIFFUSEEFFECT_H
#define KUESA_IRODIFFUSEEFFECT_H

#include <Qt3DRender/QEffect>
#include <Kuesa/kuesa_global.h>


QT_BEGIN_NAMESPACE

namespace Kuesa {

class IroDiffuseTechnique;

class KUESASHARED_EXPORT IroDiffuseEffect : public Qt3DRender::QEffect
{
    Q_OBJECT
    Q_PROPERTY(bool doubleSided READ isDoubleSided WRITE setDoubleSided NOTIFY doubleSidedChanged)
    Q_PROPERTY(bool useSkinning READ useSkinning WRITE setUseSkinning NOTIFY useSkinningChanged)
    Q_PROPERTY(bool opaque READ isOpaque WRITE setOpaque NOTIFY opaqueChanged)
    Q_PROPERTY(bool alphaCutoffEnabled READ isAlphaCutoffEnabled WRITE setAlphaCutoffEnabled NOTIFY alphaCutoffEnabledChanged)

public:
    Q_INVOKABLE explicit IroDiffuseEffect(Qt3DCore::QNode *parent = nullptr);
    ~IroDiffuseEffect();

    bool isDoubleSided() const;
    bool useSkinning() const;
    bool isOpaque() const;
    bool isAlphaCutoffEnabled() const;

public Q_SLOTS:
    void setDoubleSided(bool doubleSided);
    void setUseSkinning(bool useSkinning);
    void setOpaque(bool opaque);
    void setAlphaCutoffEnabled(bool enabled);

Q_SIGNALS:
    void doubleSidedChanged(bool doubleSided);
    void useSkinningChanged(bool useSkinning);
    void opaqueChanged(bool opaque);
    void alphaCutoffEnabledChanged(bool enabled);

private:
    bool m_useSkinning;
    bool m_opaque;
    bool m_alphaCutoffEnabled;
    IroDiffuseTechnique *m_gl3Technique;
    IroDiffuseTechnique *m_es3Technique;
    IroDiffuseTechnique *m_es2Technique;
};

} // namespace Kuesa

QT_END_NAMESPACE

#endif // KUESA_IRODIFFUSEEFFECT_H
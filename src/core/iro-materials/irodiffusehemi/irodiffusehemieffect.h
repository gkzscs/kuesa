
/*
    irodiffusehemieffect.h

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

#ifndef KUESA_IRODIFFUSEHEMIEFFECT_H
#define KUESA_IRODIFFUSEHEMIEFFECT_H

#include <Kuesa/gltf2materialeffect.h>
#include <Kuesa/kuesa_global.h>


QT_BEGIN_NAMESPACE

namespace Kuesa {

class IroDiffuseHemiTechnique;

class KUESASHARED_EXPORT IroDiffuseHemiEffect : public GLTF2MaterialEffect
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit IroDiffuseHemiEffect(Qt3DCore::QNode *parent = nullptr);
    ~IroDiffuseHemiEffect();

private:
    IroDiffuseHemiTechnique *m_gl3Technique;
    IroDiffuseHemiTechnique *m_es3Technique;
    IroDiffuseHemiTechnique *m_es2Technique;

    void updateDoubleSided(bool doubleSided) override;
    void updateSkinning(bool useSkinning) override;
    void updateOpaque(bool opaque) override;
    void updateAlphaCutoffEnabled(bool enabled) override;
};

} // namespace Kuesa

QT_END_NAMESPACE

#endif // KUESA_IRODIFFUSEHEMIEFFECT_H

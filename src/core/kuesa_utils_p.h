/*
    kuesa_utils_p.h

    This file is part of Kuesa.

    Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Mike Krus <mike.krus@kdab.com>

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

#ifndef KUESA_UTILS_P_H
#define KUESA_UTILS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Kuesa API.  It exists for the convenience
// of other Kuesa classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/QtGlobal>
#include <QtCore/QVector>
#include <Qt3DCore/QEntity>

QT_BEGIN_NAMESPACE

namespace Kuesa {

template<typename ComponentType>
inline ComponentType *componentFromEntity(Qt3DCore::QEntity *e)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    const auto cmps = e->componentsOfType<ComponentType>();
    return cmps.size() > 0 ? cmps.first() : nullptr;
#else
    ComponentType *typedComponent = nullptr;
    const Qt3DCore::QComponentVector cmps = e->components();

    for (Qt3DCore::QComponent *c : cmps) {
        typedComponent = qobject_cast<ComponentType *>(c);
        if (typedComponent != nullptr)
            break;
    }

    return typedComponent;
#endif
}

template<typename ComponentType>
inline QVector<ComponentType *> componentsFromEntity(const Qt3DCore::QEntity *e)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    return e->componentsOfType<ComponentType>();
#else
    QVector<ComponentType *> res;
    ComponentType *typedComponent = nullptr;
    const Qt3DCore::QComponentVector cmps = e->components();

    for (Qt3DCore::QComponent *c : cmps) {
        typedComponent = qobject_cast<ComponentType *>(c);
        if (typedComponent != nullptr)
            res << typedComponent;
    }

    return res;
#endif
}

} // namespace Kuesa

QT_END_NAMESPACE

#endif // KUESA_UTILS_P_H

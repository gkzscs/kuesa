/*
    tst_textureimagecollection.cpp

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

#include <QtTest/QtTest>

#include <Kuesa/textureimagecollection.h>

class tst_TextureImageCollection : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldCreateAssets()
    {
        // GIVEN
        Kuesa::TextureImageCollection collection;

        // WHEN
        Qt3DRender::QTextureImage *loader = collection.add(QStringLiteral("loader"), QUrl("foo://bar"));

        // THEN
        QVERIFY(loader);
        QCOMPARE(loader->source(), QUrl("foo://bar"));
        QCOMPARE(loader->objectName(), QStringLiteral("loader"));
        QCOMPARE(collection.names().size(), 1);
        QCOMPARE(collection.find("loader"), loader);
    }
};

QTEST_GUILESS_MAIN(tst_TextureImageCollection)
#include "tst_textureimagecollection.moc"

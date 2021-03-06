# manyducks.pro
#
# This file is part of Kuesa.
#
# Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
# Author: Jean-Michaël Celerier <jean-michael.celerier@kdab.com>
#
# Licensees holding valid proprietary KDAB Kuesa licenses may use this file in
# accordance with the Kuesa Enterprise License Agreement provided with the Software in the
# LICENSE.KUESA.ENTERPRISE file.
#
# Contact info@kdab.com if any conditions of this licensing are not clear to you.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

TEMPLATE = app

TARGET = manyducks

QT += 3dcore 3drender 3dinput 3dextras kuesa
SOURCES += \
    main.cpp

macos: APP_PWD=$$OUT_PWD/$${TARGET}.app/Contents
else:windows:APP_PWD=$$[QT_INSTALL_EXAMPLES]/kuesa/$$TARGET
else: APP_PWD=$$OUT_PWD
RES_PWD=$$APP_PWD/resources

android {
    envmaps_dir = ../assets/envmaps
    envmaps.files = \
        $${envmaps_dir}/pink_sunrise/pink_sunrise_16f_irradiance.dds \
        $${envmaps_dir}/pink_sunrise/pink_sunrise_16f_radiance.dds \
        $${envmaps_dir}/pink_sunrise/pink_sunrise_16f_specular.dds \
        $${envmaps_dir}/pink_sunrise/pink_sunrise_skybox.dds

    model_dir = ../assets/models/duck
    model.files = \
        $${model_dir}/Duck.glb

    envmaps.path = /assets
    model.path = /assets

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    DISTFILES += android/AndroidManifest.xml
    INSTALLS += envmaps model
} else {
    RCC_BINARY_SOURCES += \
        ../assets/models/duck/Duck.qrc \
        ../assets/envmaps/pink_sunrise/envmap-pink-sunrise-16f.qrc

    asset_builder.commands = $$[QT_HOST_BINS]/rcc -binary ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT} -no-compress
    asset_builder.depend_command = $$[QT_HOST_BINS]/rcc -list $$QMAKE_RESOURCE_FLAGS ${QMAKE_FILE_IN}
    asset_builder.input = RCC_BINARY_SOURCES
    asset_builder.output = $$RES_PWD/${QMAKE_FILE_IN_BASE}.qrb
    asset_builder.CONFIG += no_link target_predeps
    QMAKE_EXTRA_COMPILERS += asset_builder

    windows {
        RC_ICONS = ../shared-utils/kuesa.ico
        DESTDIR = $$[QT_INSTALL_EXAMPLES]/kuesa/$$TARGET
    } else:ios {
        envmaps_dir = ../assets/envmaps
        resfiles.files = \
            $$RES_PWD/Duck.qrb \
            $$RES_PWD/envmap-pink-sunrise-16f.qrb
        resfiles.path = "/Library/Application Support"

        QMAKE_BUNDLE_DATA += resfiles

        OTHER_FILES += Info-ios.plist
        QMAKE_INFO_PLIST = Info-ios.plist

        OBJECTIVE_SOURCES += ios/iosutils.mm
        QMAKE_ASSET_CATALOGS += ios/Images.xcassets
    } else:macos {
        ICON = ../shared-utils/kuesa.icns
        OTHER_FILES += Info-macos.plist
        QMAKE_INFO_PLIST = Info-macos.plist
    }
}

target.path = $$[QT_INSTALL_EXAMPLES]/kuesa/$$TARGET
INSTALLS += target

OTHER_FILES += doc/src/* \
    ../assets/models/duck/Duck.qrc \
    ../assets/envmaps/pink_sunrise/envmap-pink-sunrise.qrc \
    doc/src/*


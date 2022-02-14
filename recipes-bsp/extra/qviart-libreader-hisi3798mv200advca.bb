SUMMARY = "player daemon helper"
MAINTAINER = "qviart"

require conf/license/license-gplv2.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "^(og2ott4k)$"

SRC_URI = "file://qviart-libreader-${SOC_FAMILY}.sh"

INITSCRIPT_NAME = "qviart-libreader"
INITSCRIPT_PARAMS = "start 05 S ."

inherit update-rc.d

S = "${WORKDIR}"

do_compile() {
}

do_install() {
	install -d ${D}${INIT_D_DIR}/
	install -m 0755 ${WORKDIR}/qviart-libreader-${SOC_FAMILY}.sh ${D}${INIT_D_DIR}/qviart-libreader
}

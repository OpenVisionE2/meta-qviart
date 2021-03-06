SUMMARY = "halt for Qviart Model ${SOC_FAMILY}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "^(og2ott4k)$"

RDEPENDS:${PN} = "harfbuzz"

SRCDATE = "20220211"

PV = "${SRCDATE}"

inherit preserve_binary update-rc.d

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."

SRC_URI  = "http://source.mynonpublic.com/qviart/${SOC_FAMILY}-hihalt-${SRCDATE}.tar.gz \
	file://suspend.sh \
	"

SRC_URI[md5sum] = "e6d91cf4fbfe115fba0347660c6f2fc2"
SRC_URI[sha256sum] = "0bb6bf24c851874d32d35a5263700398dcf69f82844eddf803809ec2e6bee388"

S = "${WORKDIR}"

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${S}/hihalt ${D}${bindir}
	install -d ${D}${INIT_D_DIR}
	install -m 0755 ${S}/suspend.sh ${D}${INIT_D_DIR}/suspend
}

do_package_qa() {
}

FILES:${PN}  = "${bindir} ${INIT_D_DIR}"

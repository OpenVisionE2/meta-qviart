SUMMARY = "shared lib for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS:${PN} = "curl"

PV = "${SRCDATE}"

inherit lib_package preserve_binary

SOLIBS = ".so"
FILES_SOLIBSDEV = ""

SRC_URI = "http://source.mynonpublic.com/qviart/${MACHINE}-hilib-${SRCDATE}.tar.gz"

S = "${WORKDIR}/hilib"

do_configure() {
}

do_compile() {
}

do_install() {
	install -d ${D}${libdir}
	install -m 0755 ${S}/*.so ${D}${libdir}/
}

do_package_qa() {
}

FILES:${PN} += "${libdir}/*"

SUMMARY = "OG2OTT4K partitions files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy update-rc.d preserve_binary

SRCDATE = "20220214"

S = "${WORKDIR}/partitions"

SRC_URI = "http://source.mynonpublic.com/qviart/${MACHINE}-partitions-${SRCDATE}.zip \
	file://flash-apploader \
	"

SRC_URI[md5sum] = "d092a4a1837eb8e5025d7621c3e21f85"
SRC_URI[sha256sum] = "20c426703a9efa498349e770261ab5c68fbf80bc8f0e5b75f99b085300d15d71"

INITSCRIPT_NAME = "flash-apploader"
INITSCRIPT_PARAMS = "start 90 S ."

ALLOW_EMPTY:${PN} = "1"
do_configure[nostamp] = "1"

do_install() {
	install -d ${D}${datadir}
	install -m 0644 ${S}/bootargs.bin ${D}${datadir}
	install -m 0644 ${S}/sbl.bin.sig ${D}${datadir}
	install -m 0644 ${S}/apploader.bin ${D}${datadir}
	install -m 0755 -d ${D}${INIT_D_DIR}
	install -m 0755 ${WORKDIR}/flash-apploader ${D}${INIT_D_DIR}
}

FILES:${PN} = "${datadir} ${sysconfdir}"

do_deploy() {
	install -d ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/fbl.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/trustedcore.img.sig.enc ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/boot.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/sbl.bin.sig ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/apploader.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/pq_param.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/emmc_partitions.xml ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/baseparam.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/logo.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
	install -m 0755 ${S}/deviceinfo.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
}

addtask deploy before do_package after do_install

require recipes-mediacenter/kodi/stb-kodi_19.bb

PROVIDES += "virtual/kodi"
RPROVIDES:${PN} += "virtual/kodi"
PROVIDES += "kodi"
RPROVIDES:${PN} += "kodi"
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRCDATE = "20210318"

SRC_URI:append = " http://source.mynonpublic.com/kodi/hiplayer_kodi_19_${SRCDATE}.tar.gz \
	file://hiplayer_19_opt.patch \
	"

SRC_URI[md5sum] = "354009435a91f1bdd81b64e6ccb446e3"
SRC_URI[sha256sum] = "25055d538fc9633cd050be3242bcdf45f5ceec9ee9b56429a231612f5160c6c7"

DEPENDS += "qviart-libs-${MACHINE}"

RDEPENDS:${PN} += "qviart-libs-${MACHINE}"
RDEPENDS:${PN} += "qviart-opengl-${SOC_FAMILY}"

do_configure:append() {
        install -d ${D}${libdir}
        install -d ${WORKDIR}/git/xbmc/platform/linux/hisi/
        install -d ${WORKDIR}/git/xbmc/cores/hiplayer/
        install -m 0755 ${WORKDIR}/hiadp.a      ${WORKDIR}/git/xbmc/platform/linux/hisi/
        install -m 0755 ${WORKDIR}/hiplayer.a   ${WORKDIR}/git/xbmc/cores/hiplayer/
}

EXTRA_OECMAKE += " \
    -DWITH_PLATFORM=clap-cortexa15 \
    -DWITH_FFMPEG=stb \
"

COMPATIBLE_MACHINE = "^(og2ott4k)$"

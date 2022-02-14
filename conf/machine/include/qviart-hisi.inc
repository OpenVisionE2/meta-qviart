# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

BOX_BRAND = "qviart"

DISTRO_FEATURES:remove = "x11 wayland"

IMAGEDIR = "qviart/${MACHINE}"

KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	qviart-dvb-modules-${MACHINE} \
	qviart-loadmodules-${SOC_FAMILY} \ 
	qviart-opengl-${SOC_FAMILY} \
	qviart-libs-${MACHINE} \
	qviart-hihalt-${SOC_FAMILY} \
	qviart-reader-${MACHINE} \
	qviart-libreader-${SOC_FAMILY} \
	qviart-partitions-${MACHINE} \
	qviart-buildimage \
	e2fsprogs-resize2fs \
	gptfdisk \
	${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'partitions-by-name' , '', d)} \
	kernel-module-extrawlan-rtl8192eu \
	firmware-rtl8192eu \
	kernel-module-mt7601u \
	firmware-mt7601u \
	kernel-module-extrawlan-rtl8822cu \
	kernel-module-extrawlan-rtl8821cu \
	firmware-8821cu \
	kernel-module-extrabt-rtkbtusb \
	"

MACHINE_FEATURES += "hisil switchoff hdmicec emmc mmc kodi19 alsa HDMI AV_JACK multitranscoding"

IMAGE_CLASSES  += "qviart-emmc2_image"
IMAGE_FSTYPES += "qviartemmc2"
IMAGE_ROOTFS_SIZE ?= "524288"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

PREFERRED_PROVIDER_virtual/kernel = "linux-qviart"
PREFERRED_VERSION_linux-qviart = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/egl ?= "qviart-opengl-${SOC_FAMILY}" 
PREFERRED_PROVIDER_virtual/libgles1 ?= "qviart-opengl-${SOC_FAMILY}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "qviart-opengl-${SOC_FAMILY}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "qviart-blindscan-${SOC_FAMILY}"
PREFERRED_RPROVIDER_showiframe = "qviart-showiframe-${SOC_FAMILY}"
PREFERRED_RPROVIDER_aio-grab = "qviart-grab-${SOC_FAMILY}"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/arm/armv7a/tune-cortexa15.inc

require conf/machine/include/soc-family.inc

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

EXTRA_OECONF:append:pn-enigma2 = "--with-lcddev=/dev/null --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250  --with-fillaccelerationthreshold=190000"

IMAGE_CMD:qviartemmc2:append = "\
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
	mv -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4 ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4; \
	cd ${IMAGE_ROOTFS}; \
	tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	mv -f ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${KERNEL_FILE}; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt; \
	cd ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions; \
	mkupdate -s 00000003-00000001-01010101 -f ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/emmc_partitions.xml -d ${DEPLOY_DIR_IMAGE}/usb_update.bin; \ 
	cd ${DEPLOY_DIR_IMAGE}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.manifest ${IMAGE_NAME}_usb.zip.manifest; \
	zip -j ${IMAGE_NAME}_recovery_emmc.zip ${DEPLOY_DIR_IMAGE}/usb_update.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/apploader.bin; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
	rm -Rf ${IMAGEDIR}; \
	rm -Rf ${IMGDEPLOYDIR}/userdata; \
	"

IMAGE_CMD:prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/userdata; \
	"

STB_PLATFORM = "qviarthisil"

EXTRA_ALSA = "mv200"

BLINDSCAN_BINARY = "qviart-blindscan"

CFLAGS:append:pn-titan = " -DCONFIG_HISILICON_FB "

CFLAGS:append:pn-titan-infobox = " -DEVENT0 -DDOUBLE "

SOC_FAMILY = "hisi3798mv200advca"
HICHIPSET = "3798mv200advca"
CHIPSET = "Hi3798Mv200advca"

KERNELVERSION = "4.4.176"

MTD_KERNEL = "mmcblk0p15"
MTD_ROOTFS = "mmcblk0p19"

RCNAME = "qviart6"

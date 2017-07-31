TARGET := VITAident
TITLE_ID := VID000162
SOURCES := src

OBJS = app.o fs.o kernel.o main.o net.o power.o utils.o res/VITAident.o \

PREFIX   = arm-vita-eabi
CC       = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS   = -Wl,-q -Wall -Werror -O3 -fno-lto
CXXFLAGS = $(CFLAGS) -std=c++11 -fno-rtti -fno-exceptions
ASFLAGS  = $(CFLAGS)

LIBDIR = 
LDFLAGS = 
LIBS := -lvita2d -lSceDisplay_stub -lSceGxm_stub \
		-lSceSysmodule_stub -lSceCtrl_stub -lScePvf_stub \
		-lSceCommonDialog_stub -lfreetype -lpng -ljpeg -lz -lm -lc \
		-lSceAppMgr_stub -lSceAppUtil_stub \
		-lSceLibKernel_stub -lSceNet_stub -lSceNetCtl_stub -lScePower_stub  -lSceVshBridge_stub \
		-lSceAVConfig_stub -lSceRegistryMgr_stub -lSceUdcd_stub -lSceUsbstorVStorDriver_stub 
		#-lSceSysmemForDriver_stub

all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -d PARENTAL_LEVEL=1 -s APP_VER=00.72 -s TITLE_ID=$(TITLE_ID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin \
		--add ../sce_sys/icon0.png=sce_sys/icon0.png \
		--add ../sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
		--add ../sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
		--add ../sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
	$(TARGET).vpk
	
eboot.bin: $(TARGET).velf
	vita-make-fself -c $< $@

%.velf: %.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: %.png
	$(PREFIX)-ld -r -b binary -o $@ $^

clean:
	@rm -rf $(TARGET).vpk $(TARGET).velf $(TARGET).elf $(TARGET).unstripped.elf $(OBJS) \
		eboot.bin param.sfo

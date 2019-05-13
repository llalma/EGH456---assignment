# invoke SourceDir generated makefile for pwmled.pem4f
pwmled.pem4f: .libraries,pwmled.pem4f
.libraries,pwmled.pem4f: package/cfg/pwmled_pem4f.xdl
	$(MAKE) -f C:\EBG349_ws\Assignment_EK_TM4C1294XL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\EBG349_ws\Assignment_EK_TM4C1294XL_TI/src/makefile.libs clean


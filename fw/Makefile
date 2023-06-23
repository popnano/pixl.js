.PHONY: app bl clean

all: bl app

bl:
	@$(MAKE) -C bootloader/

app:
	@$(MAKE) -C application/ full
	

clean:
	@rm -rf _build/
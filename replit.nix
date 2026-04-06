{ pkgs }: {
	deps = [
   pkgs.zip
   pkgs.plan9port
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}
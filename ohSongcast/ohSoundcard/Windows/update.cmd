copy sneaky.inf pkg\sneaky.inf
copy drmsimp\objchk_win7_amd64\amd64\vaddrms.sys pkg\sneaky.sys
inf2cat.exe /driver:pkg /os:Vista_X86,Vista_X64,7_X86,7_X64 /v
SignTool sign /s PrivateCertStore pkg\sneaky.cat
SignTool sign /s PrivateCertStore pkg\sneaky.sys
%basedir%\tools\devcon\amd64\devcon.exe update pkg\sneaky.inf {4d36e96c-e325-11ce-bfc1-08002be10318}\SneakySoundcard

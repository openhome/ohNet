copy sneaky.inf pkg\sneaky.inf
copy drmsimp\objchk_win7_amd64\amd64\vaddrms.sys pkg\sneaky.sys
certmgr -del -all -s PrivateCertStore
set CERTDIR=%CD%\pkg
makecert -r -pe -ss PrivateCertStore -n "CN=TestCertforWDK" pkg\testcert.cer
inf2cat.exe /driver:pkg /os:Vista_X86,Vista_X64,7_X86,7_X64 /v
signtool sign /s PrivateCertStore pkg\sneaky.cat
signtool sign /s PrivateCertStore pkg\sneaky.sys
certmgr.exe -add pkg\testcert.cer -s -r localMachine root 
certmgr.exe -add pkg\testcert.cer -s -r localMachine trustedpublisher
%basedir%\tools\devcon\amd64\devcon.exe install pkg\sneaky.inf {4d36e96c-e325-11ce-bfc1-08002be10318}\SneakySoundcard

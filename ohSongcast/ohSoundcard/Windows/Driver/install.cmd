copy ohSoundcard.inf pkg\ohSoundcard.inf
copy drmsimp\objchk_win7_amd64\amd64\vaddrms.sys pkg\ohSoundcard.sys
certmgr -del -all -s PrivateCertStore
set CERTDIR=%CD%\pkg
makecert -r -pe -ss PrivateCertStore -n "CN=TestCertforWDK" pkg\testcert.cer
inf2cat.exe /driver:pkg /os:Vista_X86,Vista_X64,7_X86,7_X64 /v
signtool sign /s PrivateCertStore pkg\ohSoundcard.cat
signtool sign /s PrivateCertStore pkg\ohSoundcard.sys
certmgr.exe -add pkg\testcert.cer -s -r localMachine root 
certmgr.exe -add pkg\testcert.cer -s -r localMachine trustedpublisher
%basedir%\tools\devcon\amd64\devcon.exe install pkg\ohSoundcard.inf {D6BAC7AB-8758-43A9-917F-D702501F4DB0}\ohSoundcard

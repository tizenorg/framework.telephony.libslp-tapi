Test-Case
------------------------------------------------------------------------------

 TETware is suck, but nevertheless we should use this tool.



Add TC code
------------------------------------------------------------------------------

1. create your code to testcase/{your-code}.c
2. add '/textcase/{your-code}' to textcase/tslist file



Build
------------------------------------------------------------------------------

$ ./gbs_setup.sh
(tizen-build-env)# cd /var/tmp/dts_fw
(tizen-build-env)# ./build.sh
(tizen-build-env)# cat results/build-tar-result-{timestamp}.journal
check the build log (ignore testcase/tet_xres: No such file or directory)
(tizen-build-env)# cat testcase/tet_captured
check the build log
(tizen-build-env)# exit



Copy to Target
------------------------------------------------------------------------------

first-time: copy TETware & all build results to target
$ ./push.sh

after-only-update
$ sdb push testcase/utc_{XXX} /opt/home/tapi/testcase/



Run
------------------------------------------------------------------------------

$ sdb shell
sh-4.1# cd /opt/home/tapi/
sh-4.1# ./execute.sh



Test Report
------------------------------------------------------------------------------

sh-4.1# cat /opt/home/tapi/result/exec-tar-result-{timestamp}.journal
check FAIL case


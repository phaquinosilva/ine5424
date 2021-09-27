rm img/app_loader* 
rm img/hello* 
rm img/loader.img
make APPLICATION=hello
make APPLICATION=app_loader
./bin/eposmkbi . ./img/loader.img ./img/app_loader ./img/hello
/usr/bin/arm-none-eabi-objcopy -O binary img/loader.img img/app_loader.bin
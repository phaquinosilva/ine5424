rm img/app_loader* 
rm img/loader.img
make APPLICATION=hello_fork
make APPLICATION=app_loader
./bin/eposmkbi . ./img/loader.img ./img/app_loader ./img/hello_fork
/usr/bin/arm-none-eabi-objcopy -O binary img/loader.img img/app_loader.bin

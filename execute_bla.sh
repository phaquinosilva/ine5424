rm img/app_loader* 
rm img/reader* 
rm img/writer* 
rm img/loader.img
make APPLICATION=writer
make APPLICATION=reader
make APPLICATION=app_loader
./bin/eposmkbi . ./img/loader.img ./img/app_loader ./img/writer ./img/reader
/usr/bin/arm-none-eabi-objcopy -O binary img/loader.img img/app_loader.bin
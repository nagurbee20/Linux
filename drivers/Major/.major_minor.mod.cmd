savedcmd_/home/cloud_user/linux/Major/major_minor.mod := printf '%s\n'   major_minor.o | awk '!x[$$0]++ { print("/home/cloud_user/linux/Major/"$$0) }' > /home/cloud_user/linux/Major/major_minor.mod

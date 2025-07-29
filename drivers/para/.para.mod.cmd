savedcmd_/home/cloud_user/linux/para/para.mod := printf '%s\n'   para.o | awk '!x[$$0]++ { print("/home/cloud_user/linux/para/"$$0) }' > /home/cloud_user/linux/para/para.mod

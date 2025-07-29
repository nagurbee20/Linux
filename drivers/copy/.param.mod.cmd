savedcmd_/home/cloud_user/linux/copy/param.mod := printf '%s\n'   param.o | awk '!x[$$0]++ { print("/home/cloud_user/linux/copy/"$$0) }' > /home/cloud_user/linux/copy/param.mod

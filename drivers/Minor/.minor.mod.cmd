savedcmd_/home/cloud_user/linux/Minor/minor.mod := printf '%s\n'   minor.o | awk '!x[$$0]++ { print("/home/cloud_user/linux/Minor/"$$0) }' > /home/cloud_user/linux/Minor/minor.mod

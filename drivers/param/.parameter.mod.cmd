savedcmd_/home/cloud_user/linux/param/parameter.mod := printf '%s\n'   parameter.o | awk '!x[$$0]++ { print("/home/cloud_user/linux/param/"$$0) }' > /home/cloud_user/linux/param/parameter.mod

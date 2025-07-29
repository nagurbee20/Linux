savedcmd_/home/cloud_user/linux/first/hello_world.mod := printf '%s\n'   hello_world.o | awk '!x[$$0]++ { print("/home/cloud_user/linux/first/"$$0) }' > /home/cloud_user/linux/first/hello_world.mod

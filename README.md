# Automatic backup system using RSYNC

This program uses rsync to transfer files from a specified folder to a remote location.


## Setup

1. Clone the repository

	`git clone https://github.com/iosifvieru/rsync-automatic-backup`

2. Compile the code using the provided Makefile.

	`make clean`

  	`make`
   
4. Command line arguments:
   
  	`-t <minutes> specifies the time between backups.`

5. Configure config file with your specifications.
   
	 	USER=tero
		IP=192.168.1.15
		SOURCE=/media/tero/HDD/__TO_CLOUD
		DESTINATION=/home/tero/Desktop/backup

Consider that RSYNC uses SSH for data transfer so you will have to configure a ssh-keygen to create a connection between local and remote server.

`man rsync`


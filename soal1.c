#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *lokasi = "/home/chendrasena26/";
//hehe
static int getattrhehe(const char *pet, struct stat *stbuf)
{
	char pethehe[1000];
	sprintf(pethehe,"%s%s",lokasi,pet);
	int res;
	res = lstat(pethehe, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int readdirhehe(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=lokasi;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",lokasi,path);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int readhehe(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=lokasi;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",lokasi,path);
	int res = 0;
    int fd = 0 ;

    if((!strstr(path,".txt"))||(!strstr(path,".doc"))||(!strstr(path,".pdf")))
    {

    }
	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations operhehe = {
	.getattr	= getattrhehe,
	.readdir	= readdirhehe,
	.read		= readhehe,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &operhehe, NULL);
}

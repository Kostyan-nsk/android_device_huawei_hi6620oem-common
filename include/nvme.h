/*
 * Copyright (C) 2016 Kostyan_nsk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>

#define NV_NAME_LENGTH		8
#define NVE_NV_DATA_SIZE	104
#define NV_READ			1	/* NV read  operation */
#define NV_WRITE		0	/* NV write operation */

#define NVE_BOARDID		0x1
#define NVE_SN			0x2
#define NVE_MACWLAN		0xC1
#define NVE_MACBT		0xC2

struct nve_info_user {
	uint32_t nv_operation;		/* 0 - write, 1 - read */
	uint32_t nv_number;		/* NV number you want to visit */
	char nv_name[NV_NAME_LENGTH];
	uint32_t valid_size;
	u_char nv_data[NVE_NV_DATA_SIZE];
};

#define NVEACCESSDATA		_IOWR('M', 25, struct nve_info_user)

int nvme_access(struct nve_info_user *info) {

	int fd, ret = 0;

	if ((fd = open("/dev/nve0", O_RDWR)) < 0)
		return -errno;

	if (ioctl(fd, NVEACCESSDATA, info) < 0)
		ret = -errno;

	close(fd);

	return ret;
}

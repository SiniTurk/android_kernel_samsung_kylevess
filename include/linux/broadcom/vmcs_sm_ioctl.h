/*****************************************************************************
*  Copyright 2011 Broadcom Corporation.  All rights reserved.
*
*  Unless you and Broadcom execute a separate written software license
*  agreement governing use of this software, this software is licensed to you
*  under the terms of the GNU General Public License version 2, available at
*  http://www.broadcom.com/licenses/GPLv2.php (the "GPL").
*
*  Notwithstanding the above, under no circumstances may you combine this
*  software in any way with any other Broadcom software provided under a
*  license other than the GPL, without Broadcom's express prior written
*  consent.
*
*****************************************************************************/

#if !defined( __VMCS_SM_IOCTL_H__INCLUDED__ )
#define __VMCS_SM_IOCTL_H__INCLUDED__

/* ---- Include Files ---------------------------------------------------- */

#if defined( __KERNEL__ )
#include <linux/types.h>            /* Needed for standard types */
#else
#include <stdint.h>
#endif

#include <linux/ioctl.h>

/* ---- Constants and Types ---------------------------------------------- */

#define VMCS_SM_RESOURCE_NAME               32
#define VMCS_SM_RESOURCE_NAME_DEFAULT       "sm-host-resource"


/* Type define used to create unique IOCTL number */
#define VMCS_SM_MAGIC_TYPE                  'I'

/* IOCTL commands */
enum vmcs_sm_cmd_e
{
   VMCS_SM_CMD_ALLOC = 0x5A,  /* Start at 0x5A arbitrarily */
   VMCS_SM_CMD_LOCK,
   VMCS_SM_CMD_UNLOCK,
   VMCS_SM_CMD_RESIZE,
   VMCS_SM_CMD_UNMAP,
   VMCS_SM_CMD_FREE,

   VMCS_SM_CMD_SIZE_USR_HANDLE,
   VMCS_SM_CMD_CHK_USR_HANDLE,

   VMCS_SM_CMD_MAPPED_USR_HANDLE,
   VMCS_SM_CMD_MAPPED_USR_ADDRESS,
   VMCS_SM_CMD_MAPPED_VC_HDL_FROM_ADDR,
   VMCS_SM_CMD_MAPPED_VC_HDL_FROM_HDL,

   VMCS_SM_CMD_VC_WALK_ALLOC,
   VMCS_SM_CMD_HOST_WALK_MAP,
   VMCS_SM_CMD_HOST_WALK_PID_ALLOC,
   VMCS_SM_CMD_HOST_WALK_PID_MAP,

   VMCS_SM_CMD_LAST           /* Do no delete */
};

/* IOCTL Data structures */
struct vmcs_sm_ioctl_alloc
{
   /* user -> kernel */
   unsigned int size;
   unsigned int num;
   char         name[VMCS_SM_RESOURCE_NAME];

   /* kernel -> user */
   unsigned int handle;
   /* unsigned int base_addr; */
};

struct vmcs_sm_ioctl_free
{
   /* user -> kernel */
   unsigned int handle;
   /* unsigned int base_addr; */
};

struct vmcs_sm_ioctl_lock_unlock
{
   /* user -> kernel */
   unsigned int handle;

   /* kernel -> user */
   unsigned int map_me;
   unsigned int addr;
};

struct vmcs_sm_ioctl_resize
{
   /* user -> kernel */
   unsigned int handle;
   unsigned int new_size;

   /* kernel -> user */
   unsigned int old_size;
};

struct vmcs_sm_ioctl_map
{
   /* user -> kernel */
   /* kernel -> user */
   unsigned int pid;
   unsigned int handle;
   unsigned int addr;
};

struct vmcs_sm_ioctl_walk
{
   /* user -> kernel */
   unsigned int pid;
};

struct vmcs_sm_ioctl_chk
{
   /* user -> kernel */
   unsigned int handle;
};

struct vmcs_sm_ioctl_size
{
   /* user -> kernel */
   unsigned int handle;

   /* kernel -> user */
   unsigned int size;
};


/* IOCTL numbers */
#define VMCS_SM_IOCTL_MEM_ALLOC           _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_ALLOC, struct vmcs_sm_ioctl_alloc )
#define VMCS_SM_IOCTL_MEM_LOCK            _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_LOCK, struct vmcs_sm_ioctl_lock_unlock )
#define VMCS_SM_IOCTL_MEM_UNLOCK          _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_UNLOCK, struct vmcs_sm_ioctl_lock_unlock )
#define VMCS_SM_IOCTL_MEM_RESIZE          _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_RESIZE, struct vmcs_sm_ioctl_resize )
#define VMCS_SM_IOCTL_MEM_UNMAP           _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_UNMAP, struct vmcs_sm_ioctl_map )
#define VMCS_SM_IOCTL_MEM_FREE            _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_FREE, struct vmcs_sm_ioctl_free )

#define VMCS_SM_IOCTL_SIZE_USR_HDL        _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_SIZE_USR_HANDLE, struct vmcs_sm_ioctl_size )
#define VMCS_SM_IOCTL_CHK_USR_HDL         _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_CHK_USR_HANDLE, struct vmcs_sm_ioctl_chk )

#define VMCS_SM_IOCTL_MAP_USR_HDL         _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_MAPPED_USR_HANDLE, struct vmcs_sm_ioctl_map )
#define VMCS_SM_IOCTL_MAP_USR_ADDRESS     _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_MAPPED_USR_ADDRESS, struct vmcs_sm_ioctl_map )
#define VMCS_SM_IOCTL_MAP_VC_HDL_FR_ADDR  _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_MAPPED_VC_HDL_FROM_ADDR, struct vmcs_sm_ioctl_map )
#define VMCS_SM_IOCTL_MAP_VC_HDL_FR_HDL   _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_MAPPED_VC_HDL_FROM_HDL, struct vmcs_sm_ioctl_map )

#define VMCS_SM_IOCTL_VC_WALK_ALLOC       _IO( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_VC_WALK_ALLOC )
#define VMCS_SM_IOCTL_HOST_WALK_MAP       _IO( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_HOST_WALK_MAP )
#define VMCS_SM_IOCTL_HOST_WALK_PID_ALLOC _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_HOST_WALK_PID_ALLOC, struct vmcs_sm_ioctl_walk )
#define VMCS_SM_IOCTL_HOST_WALK_PID_MAP   _IOR( VMCS_SM_MAGIC_TYPE, VMCS_SM_CMD_HOST_WALK_PID_MAP, struct vmcs_sm_ioctl_walk )

/* ---- Variable Externs ------------------------------------------------- */

/* ---- Function Prototypes ---------------------------------------------- */

#endif /* __VMCS_SM_IOCTL_H__INCLUDED__ */
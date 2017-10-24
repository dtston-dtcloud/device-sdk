#ifndef _DRV_MAC_H_
#define _DRV_MAC_H_

#include <ssv6200_reg.h>


#define PHOTOTYPE_MACTYPE_ADDR(_csr)    unsigned int _csr(unsigned char *mac)

#define SW_MAC_RESET			    SET_MAC_SW_RST(0x1);

#define SET_BA_CTRL_REPLY(_val_)	(SET_BA_CTRL(((_val_ << 0) | ((GET_BA_CTRL) & 0xfffffffe))))
#define GET_BA_CTRL_REPLY(_val_)	((GET_BA_CTRL & 0x00000001) >> 0)

#define SET_BA_CTRL_ACCEPT(_val_)	(SET_BA_CTRL(((_val_ << 1) | ((GET_BA_CTRL) & 0xfffffffd))))
#define GET_BA_CTRL_ACCEPT(_val_)	((GET_BA_CTRL & 0x00000002) >> 1)

#define SET_BA_CTRL_AGRE(_val_)		(SET_BA_CTRL(((_val_ << 3) | ((GET_BA_CTRL) & 0xfffffff7))))
#define GET_BA_CTRL_AGRE(_val_)		((GET_BA_CTRL & 0x00000008) >> 3)

#define GET_MRX_BAR_RECEIVE_CNT     GET_MRX_BAR_NTF
#define GET_MRX_BA_TRANSMIT_CNT		GET_MRX_BA_NTF
#define GET_MRX_ACK_TRANSMIT_CNT	GET_MRX_DAT_NTF
#define GET_MTX_ACK_TRANSMIT_CNT	GET_MTX_ACK_TX

#define SET_MIB_FULL_EN(_val_)		(REG32(ADR_MIB_EN)) = (_val_)


PHOTOTYPE_MACTYPE_ADDR(SET_STA_MAC); 
PHOTOTYPE_MACTYPE_ADDR(GET_STA_MAC); 

PHOTOTYPE_MACTYPE_ADDR(SET_BSSID); 
PHOTOTYPE_MACTYPE_ADDR(GET_BSSID); 

PHOTOTYPE_MACTYPE_ADDR(SET_PEER_MAC0);
PHOTOTYPE_MACTYPE_ADDR(GET_PEER_MAC0);
PHOTOTYPE_MACTYPE_ADDR(SET_PEER_MAC1);
PHOTOTYPE_MACTYPE_ADDR(GET_PEER_MAC1);

PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_TB0);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_TB0);
PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_TB1);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_TB1);
PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_TB2);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_TB2);
PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_TB3);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_TB3);

PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_MASK0);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_MASK0);
PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_MASK1);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_MASK1);
PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_MASK2);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_MASK2);
PHOTOTYPE_MACTYPE_ADDR(SET_MRX_MCAST_MASK3);
PHOTOTYPE_MACTYPE_ADDR(GET_MRX_MCAST_MASK3);

PHOTOTYPE_MACTYPE_ADDR(SET_BA_TA);
PHOTOTYPE_MACTYPE_ADDR(GET_BA_TA);

PHOTOTYPE_MACTYPE_ADDR(SET_ACK_GEN_RA);
PHOTOTYPE_MACTYPE_ADDR(GET_ACK_GEN_RA);


#endif /* _DRV_MAC_H_ */

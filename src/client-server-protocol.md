# Client-server protocol description
This document is in WIP state; feel free to submit improvements.

## Suggestion number one:
1. First byte is a command ID
2. Other bytes are the command arguments

### Protocol description (subject to change)
```C++
/* 0x00 ~ 0x0F service messages */
#define MSG_NULL            0x00 /* ping                                      */
#define MSG_CTOS_GENERIC    0x01 /* client to server, debugging purposes      */
#define MSG_IDENTIFY_REQ    0x02 /* s2c, auth/id request by server            */
#define MSG_IDENTIFY_RESP   0x03 /* c2s, response to auth request             */
#define MSG_IDENTIFY_ACC    0x04 /* s2c, auth request accepted                */
#define MSG_IDENTIFY_REJ    0x05 /* s2c, auth request rejected, drop client   */
#define MSG_DISCONNECT      0x06 /* c2s, disconnect request                   */
#define MSG_FLOAT_PRECISION 0x07 /* s2c, precision for floats (32/64 bit)     */
#define MSG_DATA_HDR        0x0A /* datagram header                           */
#define MSG_DATA            0x0B /* datagram part                             */
#define MSG_EXT_OBJ         0x0E /* message is related to some object         */
#define MSG_EXT_OBJ_GRP     0x0F /* message is related to some object group   */
/* 0x10 ~ 0x1F chat/console/DCC */
#define MSG_CMD             0x10 /* generic command                           */
#define MSG_JOIN            0x11 /* join #channel                             */
#define MSG_PART            0x12 /* leave #channel                            */
#define MSG_SAY             0x13 /* say to #channel                           */
#define MSG_ME              0x14 /* IRC /me equivalent                        */
#define MSG_DCC_INIT        0x15 /* c2s, request DCC connection               */
#define MSG_DCC_ACC         0x16 /* s2c, connection accepted                  */
#define MSG_DCC_REJ         0x17 /* s2c, connection rejected                  */
#define MSG_DCC_DATA_HDR    0x18 /* c2c, datagram header                      */
#define MSG_DCC_DATA        0x19 /* c2c, datagram part                        */
#define MSG_DCC_GENERIC     0x1A /* c2c, generic message                      */
#define MSG_DCC_KILL        0x1B /* c2c, kill DCC connection                  */
#define MSG_MSG             0x1C /* c2s, private message                      */
#define MSG_X_AV            0x1E /* audio/video stream                        */
/* 0x20 ~ 0x7F ingame service messages */
#define MSG_SETHP
/* 0x80 ~ 0x9F ingame interaction messages: animation and movement */
#define MSG_MOVE            0x80 /* Move with specified velocity and direction*/
#define MSG_ACCEL           0x81 /* accelerate ACCELERATION DIR               */
#define MSG_QROT            0x82 /* quaternion rotation                       */
#define MSG_QACCEL          0x83 /* quaternion acceleration                   */
#define MSG_YAW             0x84 /* rotate along XZ plane (steering a car)    */
#define MSG_PITCH           0x85 /* rotate along YZ plane (jet up/down)       */
#define MSG_ROLL            0x86 /* rotate along XY plane (do a barrell roll) */
#define MSG_YAW_ACCEL       0x87 /* yaw acceleration                          */
#define MSG_PITCH_ACCEL     0x88 /* pitch acceleration                        */
#define MSG_ROLL_ACCEL      0x89 /* roll acceleration                         */
#define MSG_JUMP            0x8A /* as it says                                */
#define MSG_008B            0x8B /* reserved                                  */
#define MSG_008C            0x8C /* reserved                                  */
#define MSG_008D            0x8D /* reserved                                  */
#define MSG_008E            0x8E /* reserved                                  */
#define MSG_008F            0x8F /* reserved                                  */
#define MSG_POSE            0x90 /* make character take specified pose        */
#define MSG_POSE_1          0x91 /* prone                         # these are */
#define MSG_POSE_2          0x92 /* prone on elbows               # poses used*/
#define MSG_POSE_3          0x93 /* crouch                        # in combat */
#define MSG_POSE_4          0x94 /* walk on ankles                # so they   */
#define MSG_POSE_5          0x95 /* sit                           # are 1 byte*/
#define MSG_POSE_6          0x96 /* duck                          # long for  */
#define MSG_POSE_7          0x97 /* stand bent forward            # greater   */
#define MSG_POSE_8          0x98 /* stand slightly bent forward   # speed and */
#define MSG_POSE_9          0x99 /* full height                   # response  */
#define MSG_ANIM            0x9A /* set animation to be played                */
#define MSG_ANIM_PLAY       0x9B /* play it                                   */
#define MSG_ANIM_STOP       0x9C /* stop it (pause)                           */
#define MSG_ANIM_DROP       0x9D /* cancel animation                          */
#define MSG_009E            0x9E /* reserved                                  */
#define MSG_009F            0x9F /* reserved                                  */
#define MSG_POSE_PRONE      MSG_POSE_1
#define MSG_POSE_ELBOWS     MSG_POSE_2
#define MSG_POSE_CROUCH     MSG_POSE_3
#define MSG_POSE_ANKLES     MSG_POSE_4
#define MSG_POSE_SIT        MSG_POSE_5
#define MSG_POSE_DUCK       MSG_POSE_6
#define MSG_POSE_HIBENT     MSG_POSE_7
#define MSG_POSE_BENT       MSG_POSE_8
#define MSG_POSE_STAND      MSG_POSE_9
/* 0xA0 ~ 0xBF ingame interaction messages: hand to hand combat */
#define MSG_HTH_a0          0xA0 /*                                           */
#define MSG_HTH_a1          0xA1 /*                                           */
#define MSG_HTH_a2          0xA2 /*                                           */
#define MSG_HTH_a3          0xA3 /*                                           */
#define MSG_HTH_a4          0xA4 /*                                           */
#define MSG_HTH_a5          0xA5 /*                                           */
#define MSG_HTH_a6          0xA6 /*                                           */
#define MSG_HTH_a7          0xA7 /*                                           */
#define MSG_HTH_a8          0xA8 /*                                           */
#define MSG_HTH_a9          0xA9 /*                                           */
#define MSG_HTH_aa          0xAA /*                                           */
#define MSG_HTH_ab          0xAB /*                                           */
#define MSG_HTH_ac          0xAC /*                                           */
#define MSG_HTH_ad          0xAD /*                                           */
#define MSG_HTH_ae          0xAE /*                                           */
#define MSG_HTH_af          0xAF /*                                           */
#define MSG_HTH_b0          0xB0 /*                                           */
#define MSG_HTH_b1          0xB1 /*                                           */
#define MSG_HTH_b2          0xB2 /*                                           */
#define MSG_HTH_b3          0xB3 /*                                           */
#define MSG_HTH_b4          0xB4 /*                                           */
#define MSG_HTH_b5          0xB5 /*                                           */
#define MSG_HTH_b6          0xB6 /*                                           */
#define MSG_HTH_b7          0xB7 /*                                           */
#define MSG_HTH_b8          0xB8 /*                                           */
#define MSG_HTH_b9          0xB9 /*                                           */
#define MSG_HTH_ba          0xBA /*                                           */
#define MSG_HTH_bb          0xBB /*                                           */
#define MSG_HTH_bc          0xBC /*                                           */
#define MSG_HTH_bd          0xBD /*                                           */
#define MSG_HTH_be          0xBE /*                                           */
#define MSG_HTH_bf          0xBF /*                                           */
/* 0xC0 ~ 0xDF ingame interaction messages: interaction with objects */
#define MSG_OBJ_CREATE      0xC0 /* create an object                          */
#define MSG_OBJ_PICK        0xC1 /* pick an object (pickable)                 */
#define MSG_OBJ_GRAB        0xC2 /* grab an object (grabable)                 */
#define MSG_OBJ_THROW       0xC3 /* throw an object (pickable/grabable)       */
#define MSG_OBJ_DROP        0xC4 /* drop an object (pickable/grabable)        */
#define MSG_OBJ_DELETE      0xC5 /* delete an object                          */
#define MSG_OBJ_ROLE        0xC6 /* set object role (ex. knife/hammer)        */
#define MSG_OBJ_PUT         0xC7 /* put an object into desired location       */
#define MSG_OBJ_00C8        0xC8 /*                                           */
#define MSG_OBJ_00C9        0xC9 /*                                           */
#define MSG_OBJ_ACT_A       0xCA /* object default action A (use, fire)       */
#define MSG_OBJ_ACT_B       0xCB /* object default action B (alt fire)        */
#define MSG_OBJ_ACT_C       0xCC /* object default action C                   */
#define MSG_OBJ_ACT_D       0xCD /* object default action D                   */
#define MSG_OBJ_ACT_E       0xCE /* object default action E                   */
#define MSG_OBJ_ACT_GENERIC 0xCF /* generic action with object                */
#define MSG_OBJ_CONNECT     0xC0 /* connect an object to an another one       */
#define MSG_OBJ_DISCONNECT  0xD1 /* disconnect an object from one/all another */
#define MSG_OBJ_COMPOSE     0xD2 /* compose 2+ objects into one new           */
#define MSG_OBJ_DECOMPOSE   0xD3 /* decompose to compartments                 */
#define MSG_OBJ_ATTACH      0xD4 /* attach A to B                             */
#define MSG_OBJ_DETACH      0xD5 /* detach A from B                           */
#define MSG_OBJ_d6          0xD6 /*                                           */
#define MSG_OBJ_d7          0xD7 /*                                           */
#define MSG_OBJ_d8          0xD8 /*                                           */
#define MSG_OBJ_d9          0xD9 /*                                           */
#define MSG_OBJ_da          0xDA /*                                           */
#define MSG_OBJ_db          0xDB /*                                           */
#define MSG_OBJ_dc          0xDC /*                                           */
#define MSG_OBJ_dd          0xDD /*                                           */
#define MSG_OBJ_de          0xDE /*                                           */
#define MSG_OBJ_df          0xDF /*                                           */
#define MSG_OBJ_ACT_DEFAULT MSG_OBJ_ACT_A
#define MSG_OBJ_ACT_FIRE    MSG_OBJ_ACT_A
#define MSG_OBJ_ACT_ALT     MSG_OBJ_ACT_B
/* 0xE0 ~ 0xFF audio/video */
#define MSG_AV_e0           0xE0 /*                                           */
#define MSG_AV_e1           0xE1 /*                                           */
#define MSG_AV_e2           0xE2 /*                                           */
#define MSG_AV_e3           0xE3 /*                                           */
#define MSG_AV_e4           0xE4 /*                                           */
#define MSG_AV_e5           0xE5 /*                                           */
#define MSG_AV_e6           0xE6 /*                                           */
#define MSG_AV_e7           0xE7 /*                                           */
#define MSG_AV_e8           0xE8 /*                                           */
#define MSG_AV_e9           0xE9 /*                                           */
#define MSG_AV_ea           0xEA /*                                           */
#define MSG_AV_eb           0xEB /*                                           */
#define MSG_AV_ec           0xEC /*                                           */
#define MSG_AV_ed           0xED /*                                           */
#define MSG_AV_ee           0xEE /*                                           */
#define MSG_AV_ef           0xEF /*                                           */
```

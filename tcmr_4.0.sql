/*==============================================================*/
/* DBMS name:      PostgreSQL 9.x                               */
/* Created on:     5/10/2015 11:18:05 AM                        */
/*==============================================================*/


drop index BENH_PK;

drop table benh;

drop index CHUC_VU_PK;

drop table chuc_vu;

drop index NGUOI_KHAM_FK;

drop index RELATIONSHIP_20_FK;

drop index BENH_GI_FK;

drop index CO_BENH_PK;

drop table co_benh;

drop index DANH_MUC_PK;

drop table danh_muc;

drop index DO_TUOI_PK;

drop table do_tuoi;

drop index CO_GIA_FK;

drop index THUOC_GIA_FK;

drop index DON_GIA_PK;

drop table don_gia;

drop index RELATIONSHIP_29_FK;

drop index RELATIONSHIP_26_FK;

drop index RELATIONSHIP_28_FK;

drop index GOM_PK;

drop table gom;

drop index LAP_HD_FK;

drop index CUA_PT_FK;

drop index HOA_DON_PK;

drop table hoa_don;

drop index RELATIONSHIP_27_FK;

drop table lich_hen;

drop index LOVACXIN_PK;

drop table lovacxin;

drop index RELATIONSHIP_24_FK;

drop index RELATIONSHIP_21_FK;

drop index MUON_TIEM_PK;

drop table muon_tiem;

drop index CO_FK;

drop index NHAN_VIEN_PK;

drop table nhan_vien;

drop index NHAP2_FK;

drop index NHAP_FK;

drop index NHAP_PK;

drop table nhap;

drop index RELATIONSHIP_25_FK;

drop table phan_quyen;

drop index RELATIONSHIP_23_FK;

drop index NGUOI_LAP_PHIEU_FK;

drop index PHIEU_HEN_PK;

drop table phieu_hen;

drop index THUOC_CA_FK;

drop index CO_PHIEU_TIEM_FK;

drop index PHIEU_TIEM_PK;

drop table phieu_tiem;

drop index PHONG_NGUA2_FK;

drop index PHONG_NGUA_FK;

drop index PHONG_NGUA_PK;

drop table phong_ngua;

drop index PHU_HOP_FK;

drop index THUOC_PK;

drop table thuoc;

drop index RELATIONSHIP_22_FK;

drop index NGUOI_TIEM_FK;

drop index CAC_LOAI_THUOC_FK;

drop index RELATIONSHIP_16_FK;

drop index TIEM_PK;

drop table tiem;

drop index TT_BENH_NHAN_PK;

drop table tt_benh_nhan;

/*==============================================================*/
/* Table: benh                                                  */
/*==============================================================*/
create table benh (
   ma_benh              VARCHAR(15)          not null,
   ten_benh             VARCHAR(150)         null,
   la_vx                BOOL                 null,
   constraint PK_BENH primary key (ma_benh)
);

/*==============================================================*/
/* Index: BENH_PK                                               */
/*==============================================================*/
create unique index BENH_PK on benh (
ma_benh
);

/*==============================================================*/
/* Table: chuc_vu                                               */
/*==============================================================*/
create table chuc_vu (
   ma_cv                VARCHAR(12)          not null,
   ten_cv               VARCHAR(40)          null,
   constraint PK_CHUC_VU primary key (ma_cv)
);

/*==============================================================*/
/* Index: CHUC_VU_PK                                            */
/*==============================================================*/
create unique index CHUC_VU_PK on chuc_vu (
ma_cv
);

/*==============================================================*/
/* Table: co_benh                                               */
/*==============================================================*/
create table co_benh (
   ma_benh              VARCHAR(15)          not null,
   ma_bn                VARCHAR(15)          not null,
   ma_nv                VARCHAR(12)          not null,
   cs_tim               INT4                 null,
   cs_ha                INT4                 null,
   chu_y                TEXT                 null,
   du_tc                BOOL                 null,
   ngay_kham            DATE                 null,
   constraint PK_CO_BENH primary key (ma_benh, ma_bn, ma_nv)
);

/*==============================================================*/
/* Index: CO_BENH_PK                                            */
/*==============================================================*/
create unique index CO_BENH_PK on co_benh (
ma_benh,
ma_bn,
ma_nv
);

/*==============================================================*/
/* Index: BENH_GI_FK                                            */
/*==============================================================*/
create  index BENH_GI_FK on co_benh (
ma_benh
);

/*==============================================================*/
/* Index: RELATIONSHIP_20_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_20_FK on co_benh (
ma_bn
);

/*==============================================================*/
/* Index: NGUOI_KHAM_FK                                         */
/*==============================================================*/
create  index NGUOI_KHAM_FK on co_benh (
ma_nv
);

/*==============================================================*/
/* Table: danh_muc                                              */
/*==============================================================*/
create table danh_muc (
   ma_dm                INT4                 not null,
   ten_phu_phi          CHAR(100)            null,
   constraint PK_DANH_MUC primary key (ma_dm)
);

/*==============================================================*/
/* Index: DANH_MUC_PK                                           */
/*==============================================================*/
create unique index DANH_MUC_PK on danh_muc (
ma_dm
);

/*==============================================================*/
/* Table: do_tuoi                                               */
/*==============================================================*/
create table do_tuoi (
   ma_dotuoi            VARCHAR(12)          null,
   do_tuoi              VARCHAR(20)          not null,
   lieu_dung            FLOAT4               null,
   dvt                  CHAR(10)             null,
   tu                   INT4                 null,
   den                  INT4                 null,
   constraint PK_DO_TUOI primary key (do_tuoi)
);

/*==============================================================*/
/* Index: DO_TUOI_PK                                            */
/*==============================================================*/
create unique index DO_TUOI_PK on do_tuoi (
do_tuoi
);

/*==============================================================*/
/* Table: don_gia                                               */
/*==============================================================*/
create table don_gia (
   ma_dongia            INT4                 not null,
   ma_dm                INT4                 null,
   ma_thuoc             VARCHAR(12)          null,
   gia                  INT4                 null,
   ngay                 DATE                 null,
   gia_ap_dung          INT4                 null,
   constraint PK_DON_GIA primary key (ma_dongia)
);

/*==============================================================*/
/* Index: DON_GIA_PK                                            */
/*==============================================================*/
create unique index DON_GIA_PK on don_gia (
ma_dongia
);

/*==============================================================*/
/* Index: THUOC_GIA_FK                                          */
/*==============================================================*/
create  index THUOC_GIA_FK on don_gia (
ma_thuoc
);

/*==============================================================*/
/* Index: CO_GIA_FK                                             */
/*==============================================================*/
create  index CO_GIA_FK on don_gia (
ma_dm
);

/*==============================================================*/
/* Table: gom                                                   */
/*==============================================================*/
create table gom (
   ma_dm                INT4                 not null,
   ma_phieu             VARCHAR(15)          not null,
   ma_hd                VARCHAR(15)          not null,
   constraint PK_GOM primary key (ma_dm, ma_phieu, ma_hd)
);

/*==============================================================*/
/* Index: GOM_PK                                                */
/*==============================================================*/
create unique index GOM_PK on gom (
ma_dm,
ma_phieu,
ma_hd
);

/*==============================================================*/
/* Index: RELATIONSHIP_28_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_28_FK on gom (
ma_dm
);

/*==============================================================*/
/* Index: RELATIONSHIP_26_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_26_FK on gom (
ma_phieu
);

/*==============================================================*/
/* Index: RELATIONSHIP_29_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_29_FK on gom (
ma_hd
);

/*==============================================================*/
/* Table: hoa_don                                               */
/*==============================================================*/
create table hoa_don (
   ma_hd                VARCHAR(15)          not null,
   ma_nv                VARCHAR(12)          not null,
   ma_phieu             VARCHAR(15)          not null,
   ngay_lap             DATE                 null,
   so_tien              INT4                 null,
   xac_nhan             BOOL                 null,
   stt                  INT4                 null,
   da_tiem              BOOL                 null,
   constraint PK_HOA_DON primary key (ma_hd)
);

/*==============================================================*/
/* Index: HOA_DON_PK                                            */
/*==============================================================*/
create unique index HOA_DON_PK on hoa_don (
ma_hd
);

/*==============================================================*/
/* Index: CUA_PT_FK                                             */
/*==============================================================*/
create  index CUA_PT_FK on hoa_don (
ma_phieu
);

/*==============================================================*/
/* Index: LAP_HD_FK                                             */
/*==============================================================*/
create  index LAP_HD_FK on hoa_don (
ma_nv
);

/*==============================================================*/
/* Table: lich_hen                                              */
/*==============================================================*/
create table lich_hen (
   ma_thuoc             VARCHAR(12)          not null,
   ma_lich_hen          VARCHAR(12)          null,
   lan_thu              INT4                 null,
   so_ngay              INT4                 null
);

/*==============================================================*/
/* Index: RELATIONSHIP_27_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_27_FK on lich_hen (
ma_thuoc
);

/*==============================================================*/
/* Table: lovacxin                                              */
/*==============================================================*/
create table lovacxin (
   ma_lo                VARCHAR(12)          not null,
   ngay_sx              DATE                 null,
   ngay_het_hg          DATE                 null,
   nha_sx               VARCHAR(1)           null,
   quoc_gia             CHAR(2)              null,
   constraint PK_LOVACXIN primary key (ma_lo)
);

/*==============================================================*/
/* Index: LOVACXIN_PK                                           */
/*==============================================================*/
create unique index LOVACXIN_PK on lovacxin (
ma_lo
);

/*==============================================================*/
/* Table: muon_tiem                                             */
/*==============================================================*/
create table muon_tiem (
   ma_benh              VARCHAR(15)          not null,
   ma_bn                VARCHAR(15)          not null,
   moi_dk               BOOL                 null,
   constraint PK_MUON_TIEM primary key (ma_benh, ma_bn)
);

/*==============================================================*/
/* Index: MUON_TIEM_PK                                          */
/*==============================================================*/
create unique index MUON_TIEM_PK on muon_tiem (
ma_benh,
ma_bn
);

/*==============================================================*/
/* Index: RELATIONSHIP_21_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_21_FK on muon_tiem (
ma_benh
);

/*==============================================================*/
/* Index: RELATIONSHIP_24_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_24_FK on muon_tiem (
ma_bn
);

/*==============================================================*/
/* Table: nhan_vien                                             */
/*==============================================================*/
create table nhan_vien (
   ma_nv                VARCHAR(12)          not null,
   ma_cv                VARCHAR(12)          not null,
   ten_nv               VARCHAR(40)          null,
   mat_khau             VARCHAR(35)          null,
   ten_dn               VARCHAR(30)          null,
   sdt                  CHAR(10)             null,
   cmnd                 CHAR(9)              null,
   que_quan             TEXT                 null,
   constraint PK_NHAN_VIEN primary key (ma_nv)
);

/*==============================================================*/
/* Index: NHAN_VIEN_PK                                          */
/*==============================================================*/
create unique index NHAN_VIEN_PK on nhan_vien (
ma_nv
);

/*==============================================================*/
/* Index: CO_FK                                                 */
/*==============================================================*/
create  index CO_FK on nhan_vien (
ma_cv
);

/*==============================================================*/
/* Table: nhap                                                  */
/*==============================================================*/
create table nhap (
   ma_lo                VARCHAR(12)          not null,
   ma_thuoc             VARCHAR(12)          not null,
   constraint PK_NHAP primary key (ma_lo, ma_thuoc)
);

/*==============================================================*/
/* Index: NHAP_PK                                               */
/*==============================================================*/
create unique index NHAP_PK on nhap (
ma_lo,
ma_thuoc
);

/*==============================================================*/
/* Index: NHAP_FK                                               */
/*==============================================================*/
create  index NHAP_FK on nhap (
ma_lo
);

/*==============================================================*/
/* Index: NHAP2_FK                                              */
/*==============================================================*/
create  index NHAP2_FK on nhap (
ma_thuoc
);

/*==============================================================*/
/* Table: phan_quyen                                            */
/*==============================================================*/
create table phan_quyen (
   ma_cv                VARCHAR(12)          not null,
   dang_ky_tt           BOOL                 null,
   kham_so_bo           BOOL                 null,
   dong_phi             BOOL                 null,
   tiem                 BOOL                 null,
   bao_cao              BOOL                 null,
   he_thong             BOOL                 null
);

/*==============================================================*/
/* Index: RELATIONSHIP_25_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_25_FK on phan_quyen (
ma_cv
);

/*==============================================================*/
/* Table: phieu_hen                                             */
/*==============================================================*/
create table phieu_hen (
   ma_phieuhen          VARCHAR(13)          not null,
   ma_bn                VARCHAR(15)          null,
   ma_nv                VARCHAR(12)          not null,
   mui_thu              INT4                 null,
   ngay_tai_hen         DATE                 null,
   ngay_lap             DATE                 null,
   khong_the_tiem       BOOL                 null,
   phieu_tiem_lan_dau   BOOL                 null,
   constraint PK_PHIEU_HEN primary key (ma_phieuhen)
);

/*==============================================================*/
/* Index: PHIEU_HEN_PK                                          */
/*==============================================================*/
create unique index PHIEU_HEN_PK on phieu_hen (
ma_phieuhen
);

/*==============================================================*/
/* Index: NGUOI_LAP_PHIEU_FK                                    */
/*==============================================================*/
create  index NGUOI_LAP_PHIEU_FK on phieu_hen (
ma_nv
);

/*==============================================================*/
/* Index: RELATIONSHIP_23_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_23_FK on phieu_hen (
ma_bn
);

/*==============================================================*/
/* Table: phieu_tiem                                            */
/*==============================================================*/
create table phieu_tiem (
   ma_phieu             VARCHAR(15)          not null,
   ma_bn                VARCHAR(15)          not null,
   ma_nv                VARCHAR(12)          not null,
   ngay_lap_pt          DATE                 null,
   constraint PK_PHIEU_TIEM primary key (ma_phieu)
);

/*==============================================================*/
/* Index: PHIEU_TIEM_PK                                         */
/*==============================================================*/
create unique index PHIEU_TIEM_PK on phieu_tiem (
ma_phieu
);

/*==============================================================*/
/* Index: CO_PHIEU_TIEM_FK                                      */
/*==============================================================*/
create  index CO_PHIEU_TIEM_FK on phieu_tiem (
ma_bn
);

/*==============================================================*/
/* Index: THUOC_CA_FK                                           */
/*==============================================================*/
create  index THUOC_CA_FK on phieu_tiem (
ma_nv
);

/*==============================================================*/
/* Table: phong_ngua                                            */
/*==============================================================*/
create table phong_ngua (
   ma_benh              VARCHAR(15)          not null,
   ma_thuoc             VARCHAR(12)          not null,
   constraint PK_PHONG_NGUA primary key (ma_benh, ma_thuoc)
);

/*==============================================================*/
/* Index: PHONG_NGUA_PK                                         */
/*==============================================================*/
create unique index PHONG_NGUA_PK on phong_ngua (
ma_benh,
ma_thuoc
);

/*==============================================================*/
/* Index: PHONG_NGUA_FK                                         */
/*==============================================================*/
create  index PHONG_NGUA_FK on phong_ngua (
ma_benh
);

/*==============================================================*/
/* Index: PHONG_NGUA2_FK                                        */
/*==============================================================*/
create  index PHONG_NGUA2_FK on phong_ngua (
ma_thuoc
);

/*==============================================================*/
/* Table: thuoc                                                 */
/*==============================================================*/
create table thuoc (
   ma_thuoc             VARCHAR(12)          not null,
   do_tuoi              VARCHAR(20)          not null,
   ten_thuoc            VARCHAR(50)          null,
   vung_tiem            VARCHAR(200)         null,
   dung_tich            FLOAT4               null,
   sl_nhac_lai          VARCHAR(4)           null,
   lieu_dung            FLOAT4               null,
   constraint PK_THUOC primary key (ma_thuoc)
);

/*==============================================================*/
/* Index: THUOC_PK                                              */
/*==============================================================*/
create unique index THUOC_PK on thuoc (
ma_thuoc
);

/*==============================================================*/
/* Index: PHU_HOP_FK                                            */
/*==============================================================*/
create  index PHU_HOP_FK on thuoc (
do_tuoi
);

/*==============================================================*/
/* Table: tiem                                                  */
/*==============================================================*/
create table tiem (
   ma_thuoc             VARCHAR(12)          not null,
   ma_phieu             VARCHAR(15)          not null,
   ma_nv                VARCHAR(12)          not null,
   ma_bn                VARCHAR(15)          null,
   ngay_tiem            DATE                 null,
   stt_lieu             INT4                 null,
   tai_hen_lan          INT4                 null,
   ngay_hen_kt          VARCHAR(20)          null,
   ngay_dk_tai_hen      DATE                 null,
   constraint PK_TIEM primary key (ma_thuoc, ma_phieu, ma_nv)
);

/*==============================================================*/
/* Index: TIEM_PK                                               */
/*==============================================================*/
create unique index TIEM_PK on tiem (
ma_thuoc,
ma_phieu,
ma_nv
);

/*==============================================================*/
/* Index: RELATIONSHIP_16_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_16_FK on tiem (
ma_thuoc
);

/*==============================================================*/
/* Index: CAC_LOAI_THUOC_FK                                     */
/*==============================================================*/
create  index CAC_LOAI_THUOC_FK on tiem (
ma_phieu
);

/*==============================================================*/
/* Index: NGUOI_TIEM_FK                                         */
/*==============================================================*/
create  index NGUOI_TIEM_FK on tiem (
ma_nv
);

/*==============================================================*/
/* Index: RELATIONSHIP_22_FK                                    */
/*==============================================================*/
create  index RELATIONSHIP_22_FK on tiem (
ma_bn
);

/*==============================================================*/
/* Table: tt_benh_nhan                                          */
/*==============================================================*/
create table tt_benh_nhan (
   ma_bn                VARCHAR(15)          not null,
   ten                  VARCHAR(50)          null,
   gioi_tinh            enum('Nam','Nu','None') null,
   ma_dc                CHAR(5)              null,
   dc_chi_tiet          CHAR(200)            null,
   sn                   DATE                 null,
   stt                  INT4                 null,
   ngay_lap             DATE                 null,
   lap_phieu            BOOL                 null,
   da_tiemlandau        BOOL                 null,
   tai_hen              BOOL                 null,
   constraint PK_TT_BENH_NHAN primary key (ma_bn)
);

/*==============================================================*/
/* Index: TT_BENH_NHAN_PK                                       */
/*==============================================================*/
create unique index TT_BENH_NHAN_PK on tt_benh_nhan (
ma_bn
);

alter table co_benh
   add constraint FK_CO_BENH_BENH_GI_BENH foreign key (ma_benh)
      references benh (ma_benh)
      on delete restrict on update restrict;

alter table co_benh
   add constraint FK_CO_BENH_NGUOI_KHA_NHAN_VIE foreign key (ma_nv)
      references nhan_vien (ma_nv)
      on delete restrict on update restrict;

alter table co_benh
   add constraint FK_CO_BENH_RELATIONS_TT_BENH_ foreign key (ma_bn)
      references tt_benh_nhan (ma_bn)
      on delete restrict on update restrict;

alter table don_gia
   add constraint FK_DON_GIA_CO_GIA_DANH_MUC foreign key (ma_dm)
      references danh_muc (ma_dm)
      on delete restrict on update restrict;

alter table don_gia
   add constraint FK_DON_GIA_THUOC_GIA_THUOC foreign key (ma_thuoc)
      references thuoc (ma_thuoc)
      on delete restrict on update restrict;

alter table gom
   add constraint FK_GOM_RELATIONS_PHIEU_TI foreign key (ma_phieu)
      references phieu_tiem (ma_phieu)
      on delete restrict on update restrict;

alter table gom
   add constraint FK_GOM_RELATIONS_DANH_MUC foreign key (ma_dm)
      references danh_muc (ma_dm)
      on delete restrict on update restrict;

alter table gom
   add constraint FK_GOM_RELATIONS_HOA_DON foreign key (ma_hd)
      references hoa_don (ma_hd)
      on delete restrict on update restrict;

alter table hoa_don
   add constraint FK_HOA_DON_CUA_PT_PHIEU_TI foreign key (ma_phieu)
      references phieu_tiem (ma_phieu)
      on delete restrict on update restrict;

alter table hoa_don
   add constraint FK_HOA_DON_LAP_HD_NHAN_VIE foreign key (ma_nv)
      references nhan_vien (ma_nv)
      on delete restrict on update restrict;

alter table lich_hen
   add constraint FK_LICH_HEN_RELATIONS_THUOC foreign key (ma_thuoc)
      references thuoc (ma_thuoc)
      on delete restrict on update restrict;

alter table muon_tiem
   add constraint FK_MUON_TIE_RELATIONS_BENH foreign key (ma_benh)
      references benh (ma_benh)
      on delete restrict on update restrict;

alter table muon_tiem
   add constraint FK_MUON_TIE_RELATIONS_TT_BENH_ foreign key (ma_bn)
      references tt_benh_nhan (ma_bn)
      on delete restrict on update restrict;

alter table nhan_vien
   add constraint FK_NHAN_VIE_CO_CHUC_VU foreign key (ma_cv)
      references chuc_vu (ma_cv)
      on delete restrict on update restrict;

alter table nhap
   add constraint FK_NHAP_NHAP_LOVACXIN foreign key (ma_lo)
      references lovacxin (ma_lo)
      on delete restrict on update restrict;

alter table nhap
   add constraint FK_NHAP_NHAP2_THUOC foreign key (ma_thuoc)
      references thuoc (ma_thuoc)
      on delete restrict on update restrict;

alter table phan_quyen
   add constraint FK_PHAN_QUY_RELATIONS_CHUC_VU foreign key (ma_cv)
      references chuc_vu (ma_cv)
      on delete restrict on update restrict;

alter table phieu_hen
   add constraint FK_PHIEU_HE_NGUOI_LAP_NHAN_VIE foreign key (ma_nv)
      references nhan_vien (ma_nv)
      on delete restrict on update restrict;

alter table phieu_hen
   add constraint FK_PHIEU_HE_RELATIONS_TT_BENH_ foreign key (ma_bn)
      references tt_benh_nhan (ma_bn)
      on delete restrict on update restrict;

alter table phieu_tiem
   add constraint FK_PHIEU_TI_CO_PHIEU__TT_BENH_ foreign key (ma_bn)
      references tt_benh_nhan (ma_bn)
      on delete restrict on update restrict;

alter table phieu_tiem
   add constraint FK_PHIEU_TI_THUOC_CA_NHAN_VIE foreign key (ma_nv)
      references nhan_vien (ma_nv)
      on delete restrict on update restrict;

alter table phong_ngua
   add constraint FK_PHONG_NG_PHONG_NGU_BENH foreign key (ma_benh)
      references benh (ma_benh)
      on delete restrict on update restrict;

alter table phong_ngua
   add constraint FK_PHONG_NG_PHONG_NGU_THUOC foreign key (ma_thuoc)
      references thuoc (ma_thuoc)
      on delete restrict on update restrict;

alter table thuoc
   add constraint FK_THUOC_PHU_HOP_DO_TUOI foreign key (do_tuoi)
      references do_tuoi (do_tuoi)
      on delete restrict on update restrict;

alter table tiem
   add constraint FK_TIEM_CAC_LOAI__PHIEU_TI foreign key (ma_phieu)
      references phieu_tiem (ma_phieu)
      on delete restrict on update restrict;

alter table tiem
   add constraint FK_TIEM_NGUOI_TIE_NHAN_VIE foreign key (ma_nv)
      references nhan_vien (ma_nv)
      on delete restrict on update restrict;

alter table tiem
   add constraint FK_TIEM_RELATIONS_THUOC foreign key (ma_thuoc)
      references thuoc (ma_thuoc)
      on delete restrict on update restrict;

alter table tiem
   add constraint FK_TIEM_RELATIONS_TT_BENH_ foreign key (ma_bn)
      references tt_benh_nhan (ma_bn)
      on delete restrict on update restrict;


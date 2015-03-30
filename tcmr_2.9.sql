/*==============================================================*/
/* DBMS name:      PostgreSQL 9.x                               */
/* Created on:     3/28/2015 6:28:27 PM                         */
/*==============================================================*/


drop trigger TRIGGER_1 on chuc_vu;

drop table benh;

drop table bo_qua;

drop table chuc_vu;

drop table co_benh;

drop table danh_muc;

drop table do_tuoi;

drop table don_gia;

drop table gom;

drop table hoa_don;

drop table lovacxin;

drop table muon_tiem;

drop table nhan_vien;

drop table nhap;

drop table phan_quyen;

drop table phieu_hen;

drop table phieu_tiem;

drop table phong_ngua;

drop table thuoc;

drop table tiem;

drop table tt_benh_nhan;

/*==============================================================*/
/* Table: benh                                                  */
/*==============================================================*/
create table benh (
   ma_benh              VARCHAR(15)          not null,
   ten_benh             VARCHAR(35)          null,
   la_vx                BOOL                 null,
   constraint PK_BENH primary key (ma_benh)
);

/*==============================================================*/
/* Table: bo_qua                                                */
/*==============================================================*/
create table bo_qua (
   ma_hd                VARCHAR(15)          not null,
   stt_                 INT4                 null,
   ngay_bo_qua          DATE                 null,
   constraint PK_BO_QUA primary key (ma_hd)
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
/* Table: danh_muc                                              */
/*==============================================================*/
create table danh_muc (
   ma_dm                INT4                 not null,
   phu_phi              INT4                 null,
   constraint PK_DANH_MUC primary key (ma_dm)
);

/*==============================================================*/
/* Table: do_tuoi                                               */
/*==============================================================*/
create table do_tuoi (
   ma_dotuoi            VARCHAR(12)          not null,
   do_tuoi              VARCHAR(30)          null,
   lieu_dung            INT4                 null,
   constraint PK_DO_TUOI primary key (ma_dotuoi)
);

/*==============================================================*/
/* Table: don_gia                                               */
/*==============================================================*/
create table don_gia (
   ma_thuoc             VARCHAR(12)          not null,
   gia                  INT4                 null,
   ngay                 DATE                 null,
   constraint PK_DON_GIA primary key (ma_thuoc)
);

/*==============================================================*/
/* Table: gom                                                   */
/*==============================================================*/
create table gom (
   ma_hd                VARCHAR(15)          not null,
   ma_dm                INT4                 not null,
   constraint PK_GOM primary key (ma_hd, ma_dm)
);

/*==============================================================*/
/* Table: hoa_don                                               */
/*==============================================================*/
create table hoa_don (
   ma_hd                VARCHAR(15)          not null,
   ma_phieu             VARCHAR(15)          not null,
   ma_nv                VARCHAR(12)          not null,
   ngay_lap             DATE                 null default CURRENT_TIMESTAMP,
   so_tien              INT4                 null,
   xac_nhan             BOOL                 null,
   stt                  INT4                 null,
   da_tiem              BOOL                 null,
   constraint PK_HOA_DON primary key (ma_hd)
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
/* Table: muon_tiem                                             */
/*==============================================================*/
create table muon_tiem (
   ma_benh              VARCHAR(15)          not null,
   ma_bn                VARCHAR(15)          not null,
   moi_dk               BOOL                 null,
   constraint PK_MUON_TIEM primary key (ma_benh, ma_bn)
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
/* Table: nhap                                                  */
/*==============================================================*/
create table nhap (
   ma_lo                VARCHAR(12)          not null,
   ma_thuoc             VARCHAR(12)          not null,
   constraint PK_NHAP primary key (ma_lo, ma_thuoc)
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
   bao_cao              BOOL                 null
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
/* Table: phong_ngua                                            */
/*==============================================================*/
create table phong_ngua (
   ma_benh              VARCHAR(15)          not null,
   ma_thuoc             VARCHAR(12)          not null,
   constraint PK_PHONG_NGUA primary key (ma_benh, ma_thuoc)
);

/*==============================================================*/
/* Table: thuoc                                                 */
/*==============================================================*/
create table thuoc (
   ma_thuoc             VARCHAR(12)          not null,
   ma_dotuoi            VARCHAR(12)          not null,
   ten_thuoc            VARCHAR(50)          null,
   vung_tiem            VARCHAR(200)         null,
   dung_tich            INT4                 null,
   sl_nhac_lai          INT4                 null,
   chu_ky               INT4                 null,
   constraint PK_THUOC primary key (ma_thuoc)
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
   ngay_hen_kt          DATE                 null,
   ngay_dk_tai_hen      DATE                 null,
   constraint PK_TIEM primary key (ma_thuoc, ma_phieu, ma_nv)
);

/*==============================================================*/
/* Table: tt_benh_nhan                                          */
/*==============================================================*/
CREATE TYPE mood AS ENUM ('Nam', 'Nu', 'None');
create table tt_benh_nhan (
   ma_bn                VARCHAR(15)          not null,
   ten                  VARCHAR(50)          null,
   gioi_tinh            mood                 null,
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

alter table bo_qua
   add constraint FK_BO_QUA_BO_QUA_HOA_DON foreign key (ma_hd)
      references hoa_don (ma_hd)
      on delete restrict on update restrict;

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
   add constraint FK_DON_GIA_THUOC_GIA_THUOC foreign key (ma_thuoc)
      references thuoc (ma_thuoc)
      on delete restrict on update restrict;

alter table gom
   add constraint FK_GOM_GOM_HOA_DON foreign key (ma_hd)
      references hoa_don (ma_hd)
      on delete restrict on update restrict;

alter table gom
   add constraint FK_GOM_GOM2_DANH_MUC foreign key (ma_dm)
      references danh_muc (ma_dm)
      on delete restrict on update restrict;

alter table hoa_don
   add constraint FK_HOA_DON_CUA_PT_PHIEU_TI foreign key (ma_phieu)
      references phieu_tiem (ma_phieu)
      on delete restrict on update restrict;

alter table hoa_don
   add constraint FK_HOA_DON_LAP_HD_NHAN_VIE foreign key (ma_nv)
      references nhan_vien (ma_nv)
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
      on delete cascade on update restrict;

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
   add constraint FK_THUOC_PHU_HOP_DO_TUOI foreign key (ma_dotuoi)
      references do_tuoi (ma_dotuoi)
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


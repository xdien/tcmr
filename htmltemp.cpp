#include "htmltemp.h"

HtmlTemp::HtmlTemp()
{
    header = "<table border=2 cellpadding=2>\
            <tbody><tr>\
            <th rowspan=3>TT</th>\
            <th rowspan=3>Địa Phương</th>\
            <th colspan=3>Tiêm Vắc xin sởi và DPT</th>\
            <th colspan=5>Vắc xin Viêm Não Nhật Bản</th>\
            <th colspan=2> Vắc xin Thương Hàn</th>\
            </tr>\
            <tr>\
            <td rowspan=2>Trẻ 18 tháng</td>\
            <td rowspan=2>Sởi</td>\
            <td rowspan=2>DPT</td>\
            <td colspan=3>Tiêm Mũi 1 và 2</td>\
            <td colspan=2>Tiêm Mũi 3</td>\
            <td rowspan=2>Số Đối Tượng</td>\
            <td rowspan=2>Số Tiêm</td>\
            </tr>\
            <tr>\
            <td>Số Đối Tượng</td>\
            <td>Mũi 1</td>\
            <td>Mũi 2</td>\
            <td>Số Dối Tượng</td>\
            <td>Mũi 3</td>\
            </tr>";
    footer= "</table>";
}

HtmlTemp::~HtmlTemp()
{

}


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
    header1 = "<table border=1>\
            <tr>\
                <td rowspan=3>Bệnh</td>\
                <td colspan=3>Dưới 1 tuổi(0 - 11 tháng)</td>\
                <td colspan=3>1 - 4 tuổi</td>\
                <td colspan=3>5 - 9 tuổi</td>\
                <td colspan=3>10 - 14 tuổi</td>\
                <td colspan=3>15 tuổi trở lên</td>\
                <td>Cộng</td>\
            </tr>\
            <tr>\
                <td>TCĐĐ</td>\
                \
                <td>Không TC</td>\
                <td>Không rõ</td>\
                <td>TCĐĐ</td>\
                \
                <td>Không TC</td>\
                <td>Không rõ</td>\
                <td>TCĐĐ</td>\
                \
                <td>Không TC</td>\
                <td>Không rõ</td>\
                <td>TCĐĐ</td>\
                \
                <td>Không TC</td>\
                <td>Không rõ</td>\
                <td>TCĐĐ</td>\
                \
                <td>Không TC</td>\
                <td>Không rõ</td>\
                <td></td>\
            </tr>\
            <tr>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
                <td>M/C</td>\
            </tr>";

            header2 = "<table border=1>";


}



HtmlTemp::~HtmlTemp()
{

}


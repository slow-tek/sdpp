#include <templatebot/templatebot.h>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ogg/ogg.h>
#include <opus/opusfile.h>

using json = nhlomann::json;

int main(int argc, char const** argv)
{
    /* Загрузка OGG файла в память
    *  Бот ожидет пакеты формата opus 2 channel stereom 48000Hz
    * 
    *  Можно использовать ffmpeg для кодировки аудио в ogg opus:
    *  ffmpeg -i /путь/к/файлу -c:a libopus -ar 48000 -ac 2 -vn -b:a 96K /путь/к/opus.ogg
    */
    
    //Загрузить токен Discord
    json configdocument;
    std::ifstream configfile("../config.json");
    
    dpp::cluster bot(configdocument["token"]);
    
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event))
    {
        if(event.get_command.name() == "join")
        {
            dpp::guild* g = dpp::find_guild(event.command.guild_id);
            //Пробуем подключиться к голосовому каналу, возвращет false 
            //если не удаётся подключиться
            if(!g->connect_member_voice(event.command.get_issuing_user()))
            {
                event.reply("Зайди в голосовой канал!");
                return;
            }
            event.reply("Зашёл в канал!");
        }
        else if (event.command.get_command_name() == "play")
        {
            //Неправильный канал или проблемы с подключением - говорим пользователю
            if(!v || !v->voiceclient || !v->voiceclient->is_ready())
            {
                event.reply("Проблемы с получением голосового канала. Убедись что я в голосовом канале!");
                return;
            }
            ogg_sync_state oy; 
            ogg_stream_state os;
            ogg_page og;
	    ogg_packet op;
	    OpusHead header;
	    char *buffer;
	        
	    FILE *fd;
	        
            //скачать видео с ютуба через yt-dlp
            //перевести его в формат ogg через ffmpeg
            //сделать многопоточную очередь + класс-обёртку для типа музыки
            //(опционально, с ют будет всё переводиться в OGG)
            
        }
    }
}
#ifndef _CONFIG_STORAGE_
#define _CONFIG_STORAGE_

#include <stdint.h>
#include "alarm_app.h"
#include "step_counter.h"
#include "comm_protocol.h"
#include "app_util.h"

#define PERSISTENT_DATA_VERSION 0x00010001

/** �ֱ����� **/
typedef struct watch_config
{
    uint8_t alarm_delay_max_count;              //�������
    uint8_t alarm_delay_time;                   //����ʱ����
    uint8_t alarm_vibra_time;                   //������ʱ��
    _Bool   debug_enable;                       //�Ƿ���ʾ����ҳ��
    
    uint8_t display_sleep_time;                 //��ʾʱ��
    
    packet_userdata step_userdata;              //�û�����
    alarm_data_item alarm_data[MAX_ALARM_COUNT];//��������
} watch_config;

/** �ֱ��������ݣ�����д��ROM **/
typedef struct watch_persistent_data
{
    watch_config        config;
    uint32_t            unix_timestamp;         //�ϴε�ʱ���
    
    packet_walkdata     step_walkdata;          //�Ʋ�������
    packet_sleepdata    step_sleepdata[10];     //˯������ 
    
    uint8_t             space[2];               //���ݲ���

} watch_persistent_data;

STATIC_ASSERT(sizeof(watch_persistent_data)%4 == 0);

/** �ֱ���ʱ���ݣ�����д��ROM **/
typedef struct watch_temporary_data
{
    uint8_t battery_level;                      //��������
    
    _Bool charge_charging;                      //�����
    _Bool charge_full;                          //����
    
    _Bool disp_awake;                           //�ֱ��Ƿ���
    
    char pair_passcode[7];                      //���������
    
    uint8_t page_current_screen;                //��ǰ��ʾҳ��
    _Bool page_should_render_every_frame;       //�Ƿ���Ⱦÿ֡
    _Bool page_keep_awake;                      //�Ƿ񱣳ֻ���
    
    float temp_current_temp;                    //��ǰ�ֱ��¶�
    
    packet_message message;                     //�·�֪ͨ��Ϣ

} watch_temporary_data;

typedef struct watch_data {
    watch_persistent_data persist;
    watch_temporary_data temporary;
} watch_data;

extern watch_data watch_config_data;
void config_init(void);
void config_write(void);
void config_load_default(void);

#endif

#include "bsp_api.h"
#include "r_flash_hp.h"
#include "r_flash_api.h"

#define FSP_GUARD_g_flash0_R_FLASH_HP_Open() g_flash0_open_guard(FSP_SECURE_ARGUMENT, FSP_SECURE_ARGUMENT)

#define FSP_GUARD_g_flash0_R_FLASH_HP_Write(src_address, flash_address, num_bytes) g_flash0_write_guard(FSP_SECURE_ARGUMENT, src_address, flash_address, num_bytes)

#define FSP_GUARD_g_flash0_R_FLASH_HP_Erase(address, num_blocks) g_flash0_erase_guard(FSP_SECURE_ARGUMENT, address, num_blocks)

#define FSP_GUARD_g_flash0_R_FLASH_HP_BlankCheck(address, num_bytes, p_blank_check_result) g_flash0_blank_check_guard(FSP_SECURE_ARGUMENT, address, num_bytes, p_blank_check_result)

#define FSP_GUARD_g_flash0_R_FLASH_HP_Close() g_flash0_close_guard(FSP_SECURE_ARGUMENT)

#define FSP_GUARD_g_flash0_R_FLASH_HP_StatusGet(p_status) g_flash0_status_get_guard(FSP_SECURE_ARGUMENT, p_status)

#define FSP_GUARD_g_flash0_R_FLASH_HP_AccessWindowSet(start_addr, end_addr) g_flash0_access_window_set_guard(FSP_SECURE_ARGUMENT, start_addr, end_addr)

#define FSP_GUARD_g_flash0_R_FLASH_HP_AccessWindowClear() g_flash0_access_window_clear_guard(FSP_SECURE_ARGUMENT)

#define FSP_GUARD_g_flash0_R_FLASH_HP_IdCodeSet(p_id_code, mode) g_flash0_id_code_set_guard(FSP_SECURE_ARGUMENT, p_id_code, mode)

#define FSP_GUARD_g_flash0_R_FLASH_HP_Reset() g_flash0_reset_guard(FSP_SECURE_ARGUMENT)

#define FSP_GUARD_g_flash0_R_FLASH_HP_UpdateFlashClockFreq() g_flash0_update_flash_clock_freq_guard(FSP_SECURE_ARGUMENT)

#define FSP_GUARD_g_flash0_R_FLASH_HP_StartUpAreaSelect(swap_type, is_temporary) g_flash0_start_up_area_select_guard(FSP_SECURE_ARGUMENT, swap_type, is_temporary)

#define FSP_GUARD_g_flash0_R_FLASH_HP_CallbackSet(p_callback, p_context, p_callback_memory) g_flash0_callback_set_guard(FSP_SECURE_ARGUMENT, p_callback, p_context, p_callback_memory)

#define FSP_GUARD_g_flash0_R_FLASH_HP_BankSwap() g_flash0_bank_swap_guard(FSP_SECURE_ARGUMENT)

#define FSP_GUARD_g_flash0_R_FLASH_HP_InfoGet(p_info) g_flash0_info_get_guard(FSP_SECURE_ARGUMENT, p_info)

#define FSP_GUARD_g_flash0_R_FLASH_HP_AntiRollbackCounterIncrement(counter) g_flash0_anti_rollback_counter_increment_guard(FSP_SECURE_ARGUMENT, counter)

#define FSP_GUARD_g_flash0_R_FLASH_HP_AntiRollbackCounterRefresh(counter) g_flash0_anti_rollback_counter_refresh_guard(FSP_SECURE_ARGUMENT, counter)

#define FSP_GUARD_g_flash0_R_FLASH_HP_AntiRollbackCounterRead(counter, p_count) g_flash0_anti_rollback_counter_read_guard(FSP_SECURE_ARGUMENT, counter, p_count)

#define FSP_GUARD_g_flash0_R_FLASH_HP_UserLockableAreaWrite(src_address, flash_address, num_bytes) g_flash0_user_lockable_area_write_guard(FSP_SECURE_ARGUMENT, src_address, flash_address, num_bytes)

#define FSP_GUARD_g_flash0_R_FLASH_HP_Read(dest_address, flash_address, num_bytes) g_flash0_read_guard(dest_address, flash_address, num_bytes)

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_open_guard(flash_ctrl_t *const p_api_ctrl, flash_cfg_t const *const p_cfg);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_write_guard(flash_ctrl_t *const p_api_ctrl, uint32_t const src_address,
        uint32_t flash_address, uint32_t const num_bytes);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_erase_guard(flash_ctrl_t *const p_api_ctrl, uint32_t const address,
        uint32_t const num_blocks);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_blank_check_guard(flash_ctrl_t *const p_api_ctrl, uint32_t const address,
        uint32_t num_bytes, flash_result_t *p_blank_check_result);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_close_guard(flash_ctrl_t *const p_api_ctrl);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_status_get_guard(flash_ctrl_t *const p_api_ctrl,
        flash_status_t *const p_status);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_access_window_set_guard(flash_ctrl_t *const p_api_ctrl,
        uint32_t const start_addr, uint32_t const end_addr);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_access_window_clear_guard(flash_ctrl_t *const p_api_ctrl);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_id_code_set_guard(flash_ctrl_t *const p_api_ctrl,
        uint8_t const *const p_id_code, flash_id_code_mode_t mode);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_reset_guard(flash_ctrl_t *const p_api_ctrl);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_update_flash_clock_freq_guard(flash_ctrl_t *const p_api_ctrl);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_start_up_area_select_guard(flash_ctrl_t *const p_api_ctrl,
        flash_startup_area_swap_t swap_type, bool is_temporary);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_callback_set_guard(flash_ctrl_t *const p_api_ctrl,
        void (*p_callback)(flash_callback_args_t*), void const *const p_context,
        flash_callback_args_t *const p_callback_memory);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_bank_swap_guard(flash_ctrl_t *const p_api_ctrl);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_info_get_guard(flash_ctrl_t *const p_api_ctrl, flash_info_t *const p_info);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_anti_rollback_counter_increment_guard(flash_ctrl_t *const p_api_ctrl,
        flash_arc_t counter);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_anti_rollback_counter_refresh_guard(flash_ctrl_t *const p_api_ctrl,
        flash_arc_t counter);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_anti_rollback_counter_read_guard(flash_ctrl_t *const p_api_ctrl,
        flash_arc_t counter, uint32_t *const p_count);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_user_lockable_area_write_guard(flash_ctrl_t *const p_api_ctrl,
        uint32_t const src_address, uint32_t flash_address, uint32_t const num_bytes);

extern BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_flash0_read_guard(uint32_t dest_address, uint32_t const flash_address, uint32_t const num_bytes);

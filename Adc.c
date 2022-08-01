/**
  * @brief  Enables ADC, starts conversion of regular group.
  *         Interruptions enabled in this function: None.
  * @param  hadc ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Perform ADC enable and conversion start if no conversion is on going */
  if (ADC_IS_CONVERSION_ONGOING_REGULAR(hadc) == RESET)
  {
    /* Process locked */
    __HAL_LOCK(hadc);
      
    /* Enable the ADC peripheral */
    /* If low power mode AutoPowerOff is enabled, power-on/off phases are     */
    /* performed automatically by hardware.                                   */
    if (hadc->Init.LowPowerAutoPowerOff != ENABLE)
    {
      tmp_hal_status = ADC_Enable(hadc);
    }
    
    /* Start conversion if ADC is effectively enabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Set ADC state                                                        */
      /* - Clear state bitfield related to regular group conversion results   */
      /* - Set state bitfield related to regular operation                    */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_READY | HAL_ADC_STATE_REG_EOC | HAL_ADC_STATE_REG_OVR | HAL_ADC_STATE_REG_EOSMP,
                        HAL_ADC_STATE_REG_BUSY);
      
      /* Reset ADC all error code fields */
      ADC_CLEAR_ERRORCODE(hadc);
      
      /* Process unlocked */
      /* Unlock before starting ADC conversions: in case of potential         */
      /* interruption, to let the process to ADC IRQ Handler.                 */
      __HAL_UNLOCK(hadc);
      
      /* Clear regular group conversion flag and overrun flag */
      /* (To ensure of no unknown state from potential previous ADC           */
      /* operations)                                                          */
      __HAL_ADC_CLEAR_FLAG(hadc, (ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_OVR));
      
      /* Enable conversion of regular group.                                  */
      /* If software start has been selected, conversion starts immediately.  */
      /* If external trigger has been selected, conversion will start at next */
      /* trigger event.                                                       */
      hadc->Instance->CR |= ADC_CR_ADSTART;
    }
  }
  else
  {
    tmp_hal_status = HAL_BUSY;
  }
  
  /* Return function status */
  return tmp_hal_status;
}
/**
  * @brief Check if no conversion on going on regular group
  * @param __HANDLE__ ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define ADC_IS_CONVERSION_ONGOING_REGULAR(__HANDLE__)                          \
  (( (((__HANDLE__)->Instance->CR) & ADC_CR_ADSTART) == RESET                  \
  ) ? RESET : SET)
  
 
/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @note   If low power mode AutoPowerOff is enabled, power-on/off phases are
  *         performed automatically by hardware.
  *         In this mode, this function is useless and must not be called because 
  *         flag ADC_FLAG_RDY is not usable.
  *         Therefore, this function must be called under condition of
  *         "if (hadc->Init.LowPowerAutoPowerOff != ENABLE)".
  * @param  hadc ADC handle
  * @retval HAL status.
  */
static HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0U;
  __IO uint32_t wait_loop_index = 0U;
  
  /* ADC enable and wait for ADC ready (in case of ADC is disabled or         */
  /* enabling phase not yet completed: flag ADC ready not yet set).           */
  /* Timeout implemented to not be stuck if ADC cannot be enabled (possible   */
  /* causes: ADC clock not running, ...).                                     */
  if (ADC_IS_ENABLE(hadc) == RESET)
  {
    /* Check if conditions to enable the ADC are fulfilled */
    if (ADC_ENABLING_CONDITIONS(hadc) == RESET)
    {
      /* Update ADC state machine to error */
      SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
    
      /* Set ADC error code to ADC IP internal error */
      SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
      
      return HAL_ERROR;
    }
    
    /* Enable the ADC peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Delay for ADC stabilization time */
    /* Compute number of CPU cycles to wait for */
    wait_loop_index = (ADC_STAB_DELAY_US * (SystemCoreClock / 1000000U));
    while(wait_loop_index != 0U)
    {
      wait_loop_index--;
    }

    /* Get tick count */
    tickstart = HAL_GetTick();
    
    /* Wait for ADC effectively enabled */
    while(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_RDY) == RESET)
    {
      if((HAL_GetTick() - tickstart) > ADC_ENABLE_TIMEOUT)
      {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
      
        /* Set ADC error code to ADC IP internal error */
        SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
      
        return HAL_ERROR;
      }
    }   
    
  }
   
  /* Return HAL status */
  return HAL_OK;
}
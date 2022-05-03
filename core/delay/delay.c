


void dwt_init(void)
{
    //разрешаем использовать счётчик
    SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    //обнуляем значение счётного регистра
	DWT_CYCCNT  = 0;
         //запускаем счётчик
	DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk; 
}
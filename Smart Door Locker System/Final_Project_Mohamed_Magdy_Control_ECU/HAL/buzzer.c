#include "buzzer.h"

void Buzzer_init(void)
{
    BUZZER_DDR |= (1 << BUZZER_PIN);   // Set buzzer pin as output
    BUZZER_PORT &= ~(1 << BUZZER_PIN); // Turn buzzer off initially
}

void Buzzer_on(void)
{
    BUZZER_PORT |= (1 << BUZZER_PIN); // Set pin high
}

void Buzzer_off(void)
{
    BUZZER_PORT &= ~(1 << BUZZER_PIN); // Set pin low
}

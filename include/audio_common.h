/* Arquivo que agrupa os codigos de status comuns a toda a biblioteca, por enquanto tem só um erro, mas eventualmente pode ser necessário adicionar mais tipos de erro */

/*
 * Enum que agrupa os status de retorno das funções
 *
 * SUCCESS: sucesso
 * ERR: erro  
 */
typedef enum {
  AL_SUCCESS = 0,
  AL_ERR = 1
} al_status;

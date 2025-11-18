#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// ========================================================================
// CONSTANTES GLOBAIS
// ========================================================================

#define TAMANHO_TABULEIRO 10    // Tabuleiro 10x10
#define TAMANHO_NAVIO 3         // Cada navio ocupa 3 posições
#define TAMANHO_HABILIDADE 5    // Matriz de habilidade 5x5
#define AGUA 0                  // Água
#define NAVIO 3                 // Navio
#define HABILIDADE 5            // Área de efeito da habilidade

int main() {
    
    /*
     * ====================================================================
     * SEÇÃO 1: DECLARAÇÃO DE VARIÁVEIS
     * ====================================================================
     */
    
    // === TABULEIRO PRINCIPAL ===
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // === MATRIZES DE HABILIDADES ===
    // Cada matriz representa a área de efeito de uma habilidade
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // === COORDENADAS DOS NAVIOS ===
    int h_linha = 1, h_coluna = 2;      // Horizontal
    int v_linha = 4, v_coluna = 7;      // Vertical
    int dd_linha = 6, dd_coluna = 1;    // Diagonal descendente
    int da_linha = 7, da_coluna = 8;    // Diagonal ascendente
    
    // === PONTOS DE ORIGEM DAS HABILIDADES ===
    // Centro onde a habilidade será aplicada
    int cone_origem_linha = 2;
    int cone_origem_coluna = 5;
    
    int cruz_origem_linha = 5;
    int cruz_origem_coluna = 4;
    
    int octaedro_origem_linha = 8;
    int octaedro_origem_coluna = 5;
    
    // === VARIÁVEIS DE CONTROLE ===
    int i, j;
    int linha_tab, coluna_tab;          // Posições no tabuleiro
    int offset = TAMANHO_HABILIDADE / 2; // Offset para centralizar (2 para matriz 5x5)
    
    /*
     * ====================================================================
     * SEÇÃO 2: APRESENTAÇÃO
     * ====================================================================
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║         BATALHA NAVAL - NÍVEL MESTRE              ║\n");
    printf("║      Habilidades Especiais e Áreas de Efeito      ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("⚡ HABILIDADES DISPONÍVEIS:\n");
    printf("   ▼ CONE - Área em forma de triângulo\n");
    printf("   + CRUZ - Área em forma de cruz\n");
    printf("   ◆ OCTAEDRO - Área em forma de losango\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 3: INICIALIZAÇÃO DO TABULEIRO
     * ====================================================================
     */
    
    printf("🌊 Inicializando tabuleiro...\n");
    
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
    
    printf("✅ Tabuleiro inicializado!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 4: POSICIONAMENTO DOS NAVIOS
     * ====================================================================
     */
    
    printf("🚢 Posicionando navios...\n");
    
    // Navio horizontal
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[h_linha][h_coluna + i] = NAVIO;
    }
    printf("   ✓ Navio horizontal: [%d][%d-%d]\n", 
           h_linha, h_coluna, h_coluna + TAMANHO_NAVIO - 1);
    
    // Navio vertical
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[v_linha + i][v_coluna] = NAVIO;
    }
    printf("   ✓ Navio vertical: [%d-%d][%d]\n", 
           v_linha, v_linha + TAMANHO_NAVIO - 1, v_coluna);
    
    // Navio diagonal descendente
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[dd_linha + i][dd_coluna + i] = NAVIO;
    }
    printf("   ✓ Navio diagonal ↘: [%d][%d] → [%d][%d]\n", 
           dd_linha, dd_coluna, dd_linha + 2, dd_coluna + 2);
    
    // Navio diagonal ascendente
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[da_linha + i][da_coluna - i] = NAVIO;
    }
    printf("   ✓ Navio diagonal ↗: [%d][%d] → [%d][%d]\n", 
           da_linha, da_coluna, da_linha + 2, da_coluna - 2);
    
    printf("✅ Todos os navios posicionados!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 5: CRIAÇÃO DA HABILIDADE CONE ▼
     * ====================================================================
     * 
     * FORMATO DO CONE (5x5):
     *     0 0 1 0 0
     *     0 1 1 1 0
     *     1 1 1 1 1
     *     0 0 0 0 0
     *     0 0 0 0 0
     * 
     * Lógica: Expande de cima para baixo, como um triângulo
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║         HABILIDADE 1: CONE ▼                       ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("🔧 Construindo matriz de efeito CONE...\n");
    
    // Inicializa matriz com zeros
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade_cone[i][j] = 0;
        }
    }
    
    // Constrói o cone usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;  // Centro = 2 (para matriz 5x5)
    
    for (i = 0; i < 3; i++) {  // Apenas 3 linhas superiores formam o cone
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar cone: distância do centro <= linha
            if (j >= (centro - i) && j <= (centro + i)) {
                habilidade_cone[i][j] = 1;
            }
        }
    }
    
    // Exibe a matriz do cone
    printf("📐 Formato do CONE:\n");
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        printf("   ");
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade_cone[i][j]);
        }
        printf("\n");
    }
    printf("✅ Cone criado!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 6: CRIAÇÃO DA HABILIDADE CRUZ +
     * ====================================================================
     * 
     * FORMATO DA CRUZ (5x5):
     *     0 0 1 0 0
     *     0 0 1 0 0
     *     1 1 1 1 1
     *     0 0 1 0 0
     *     0 0 1 0 0
     * 
     * Lógica: Linha central completa + coluna central completa
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║         HABILIDADE 2: CRUZ +                       ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("🔧 Construindo matriz de efeito CRUZ...\n");
    
    // Inicializa matriz com zeros
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade_cruz[i][j] = 0;
        }
    }
    
    // Constrói a cruz usando condicionais
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cruz: linha central OU coluna central
            if (i == centro || j == centro) {
                habilidade_cruz[i][j] = 1;
            }
        }
    }
    
    // Exibe a matriz da cruz
    printf("📐 Formato da CRUZ:\n");
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        printf("   ");
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade_cruz[i][j]);
        }
        printf("\n");
    }
    printf("✅ Cruz criada!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 7: CRIAÇÃO DA HABILIDADE OCTAEDRO ◆
     * ====================================================================
     * 
     * FORMATO DO OCTAEDRO/LOSANGO (5x5):
     *     0 0 1 0 0
     *     0 1 1 1 0
     *     1 1 1 1 1
     *     0 1 1 1 0
     *     0 0 1 0 0
     * 
     * Lógica: Distância Manhattan do centro <= raio
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║         HABILIDADE 3: OCTAEDRO ◆                   ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("🔧 Construindo matriz de efeito OCTAEDRO...\n");
    
    // Inicializa matriz com zeros
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade_octaedro[i][j] = 0;
        }
    }
    
    // Constrói o octaedro usando distância Manhattan
    int raio = centro;  // Raio = 2
    
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Distância Manhattan: |i - centro| + |j - centro|
            int dist_linha = (i > centro) ? (i - centro) : (centro - i);
            int dist_coluna = (j > centro) ? (j - centro) : (centro - j);
            int distancia = dist_linha + dist_coluna;
            
            // Se distância <= raio, está dentro do losango
            if (distancia <= raio) {
                habilidade_octaedro[i][j] = 1;
            }
        }
    }
    
    // Exibe a matriz do octaedro
    printf("📐 Formato do OCTAEDRO:\n");
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        printf("   ");
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade_octaedro[i][j]);
        }
        printf("\n");
    }
    printf("✅ Octaedro criado!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 8: APLICAÇÃO DO CONE NO TABULEIRO
     * ====================================================================
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║      APLICANDO HABILIDADE CONE NO TABULEIRO       ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("🎯 Origem do CONE: [%d][%d]\n", cone_origem_linha, cone_origem_coluna);
    printf("⚡ Aplicando área de efeito...\n");
    
    // Percorre a matriz de habilidade
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Verifica se esta posição da habilidade está ativa
            if (habilidade_cone[i][j] == 1) {
                // Calcula posição no tabuleiro
                linha_tab = cone_origem_linha - offset + i;
                coluna_tab = cone_origem_coluna - offset + j;
                
                // Verifica se está dentro dos limites do tabuleiro
                if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO &&
                    coluna_tab >= 0 && coluna_tab < TAMANHO_TABULEIRO) {
                    
                    // Não sobrescreve navios, apenas marca áreas vazias
                    if (tabuleiro[linha_tab][coluna_tab] != NAVIO) {
                        tabuleiro[linha_tab][coluna_tab] = HABILIDADE;
                    }
                }
            }
        }
    }
    
    printf("✅ CONE aplicado!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 9: EXIBIÇÃO DO TABULEIRO COM CONE
     * ====================================================================
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║        TABULEIRO COM HABILIDADE CONE              ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    // Cabeçalho
    printf("    ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d ", j);
    }
    printf("\n   ┌");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("───");
    }
    printf("┐\n");
    
    // Corpo do tabuleiro
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d │", i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" ~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" ■ ");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf(" ▼ ");  // Símbolo do cone
            }
        }
        printf("│\n");
    }
    
    // Rodapé
    printf("   └");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("───");
    }
    printf("┘\n\n");
    
    printf("📋 LEGENDA:\n");
    printf("   ~ = Água\n");
    printf("   ■ = Navio\n");
    printf("   ▼ = Área de efeito do CONE\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 10: RESETAR E APLICAR CRUZ
     * ====================================================================
     */
    
    // Limpa áreas de habilidade anteriores
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == HABILIDADE) {
                tabuleiro[i][j] = AGUA;
            }
        }
    }
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║      APLICANDO HABILIDADE CRUZ NO TABULEIRO       ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("🎯 Origem da CRUZ: [%d][%d]\n", cruz_origem_linha, cruz_origem_coluna);
    printf("⚡ Aplicando área de efeito...\n");
    
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade_cruz[i][j] == 1) {
                linha_tab = cruz_origem_linha - offset + i;
                coluna_tab = cruz_origem_coluna - offset + j;
                
                if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO &&
                    coluna_tab >= 0 && coluna_tab < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha_tab][coluna_tab] != NAVIO) {
                        tabuleiro[linha_tab][coluna_tab] = HABILIDADE;
                    }
                }
            }
        }
    }
    
    printf("✅ CRUZ aplicada!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 11: EXIBIÇÃO DO TABULEIRO COM CRUZ
     * ====================================================================
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║        TABULEIRO COM HABILIDADE CRUZ              ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("    ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d ", j);
    }
    printf("\n   ┌");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("───");
    }
    printf("┐\n");
    
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d │", i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" ~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" ■ ");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf(" + ");  // Símbolo da cruz
            }
        }
        printf("│\n");
    }
    
    printf("   └");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("───");
    }
    printf("┘\n\n");
    
    printf("📋 LEGENDA:\n");
    printf("   ~ = Água\n");
    printf("   ■ = Navio\n");
    printf("   + = Área de efeito da CRUZ\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 12: RESETAR E APLICAR OCTAEDRO
     * ====================================================================
     */
    
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == HABILIDADE) {
                tabuleiro[i][j] = AGUA;
            }
        }
    }
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║    APLICANDO HABILIDADE OCTAEDRO NO TABULEIRO     ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("🎯 Origem do OCTAEDRO: [%d][%d]\n", octaedro_origem_linha, octaedro_origem_coluna);
    printf("⚡ Aplicando área de efeito...\n");
    
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade_octaedro[i][j] == 1) {
                linha_tab = octaedro_origem_linha - offset + i;
                coluna_tab = octaedro_origem_coluna - offset + j;
                
                if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO &&
                    coluna_tab >= 0 && coluna_tab < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha_tab][coluna_tab] != NAVIO) {
                        tabuleiro[linha_tab][coluna_tab] = HABILIDADE;
                    }
                }
            }
        }
    }
    
    printf("✅ OCTAEDRO aplicado!\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 13: EXIBIÇÃO DO TABULEIRO COM OCTAEDRO
     * ====================================================================
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║      TABULEIRO COM HABILIDADE OCTAEDRO            ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("    ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d ", j);
    }
    printf("\n   ┌");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("───");
    }
    printf("┐\n");
    
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d │", i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" ~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" ■ ");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf(" ◆ ");  // Símbolo do octaedro
            }
        }
        printf("│\n");
    }
    
    printf("   └");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("───");
    }
    printf("┘\n\n");
    
    printf("📋 LEGENDA:\n");
    printf("   ~ = Água\n");
    printf("   ■ = Navio\n");
    printf("   ◆ = Área de efeito do OCTAEDRO\n\n");
    
    /*
     * ====================================================================
     * SEÇÃO 14: RESUMO FINAL
     * ====================================================================
     */
    
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║    🏆 DESAFIO FINAL CONCLUÍDO COM SUCESSO! 🏆     ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    printf("✅ CONQUISTAS DESBLOQUEADAS:\n");
    printf("   🎯 3 Habilidades implementadas\n");
    printf("   📐 Matrizes dinâmicas criadas com condicionais\n");
    printf("   🗺️  Áreas de efeito sobrepostas ao tabuleiro\n");
    printf("   🛡️  Validação de limites completa\n");
    printf("   🎨 Visualização clara e organizada\n\n");
    
    return 0;
}

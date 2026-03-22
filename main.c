#include <stdio.h>

typedef struct {
    double receitaBruta;
    double deducoes;
    double custoMercadorias;
    double despesasOperacionais;
    double despesasFinanceiras;
    double receitasFinanceiras;
    double impostoRenda;
    double csl;
} DRE;

typedef struct {
    // Ativo
    double caixa, bancos, aplicacoes, contasReceber, estoques;
    double realizavelLP, investimentos, imobilizado, intangivel;
    // Passivo
    double fornecedores, contasPagar;
    double emprestimosLP, provisoes;
    // Patrimonio Liquido
    double capitalSocial, reservasCapital, reservasLucros, lucrosAcumulados;
} Balanco;

typedef struct {
    // Resultados
    double lucroBruto;
    double lucroOperacional;
    double lucroAntesIR;
    double lucroLiquido;
} Resultado;

void calcularDRE(DRE *dre, Resultado *res) {
    double receitaLiquida = dre->receitaBruta - dre->deducoes;
    res->lucroBruto = receitaLiquida - dre->custoMercadorias;
    res->lucroOperacional = res->lucroBruto - dre->despesasOperacionais;
    res->lucroAntesIR = res->lucroOperacional - dre->despesasFinanceiras + dre->receitasFinanceiras;
    res->lucroLiquido = res->lucroAntesIR - dre->impostoRenda - dre->csl;

    printf("\n--- DRE ---\n");
    printf("Receita Liquida:\tR$ %.2f\n", receitaLiquida);
    printf("Lucro Bruto:\t\tR$ %.2f\n", res->lucroBruto);
    printf("Lucro Operacional:\tR$ %.2f\n", res->lucroOperacional);
    printf("Lucro Antes IR:\t\tR$ %.2f\n", res->lucroAntesIR);
    printf("Lucro Liquido:\t\tR$ %.2f\n", res->lucroLiquido);
}

void calcularBalanco(Balanco *balanco, Resultado *res) {
    double totalAtivo = balanco->caixa + balanco->bancos + balanco->aplicacoes + balanco->contasReceber + balanco->estoques
                       + balanco->realizavelLP + balanco->investimentos + balanco->imobilizado + balanco->intangivel;
    
    double totalPassivo = balanco->fornecedores + balanco->contasPagar + balanco->emprestimosLP + balanco->provisoes;
    
    double totalPL = balanco->capitalSocial + balanco->reservasCapital + balanco->reservasLucros + balanco->lucrosAcumulados + res->lucroLiquido;

    printf("\n--- BALANCO PATRIMONIAL ---\n");
    printf("Total Ativo:\t\tR$ %.2f\n", totalAtivo);
    printf("Total Passivo:\t\tR$ %.2f\n", totalPassivo);
    printf("Total Patrimonio Liquido:\tR$ %.2f\n", totalPL);

    if(totalAtivo == totalPassivo + totalPL)
        printf("Equacao Fundamental: OK (Ativo = Passivo + PL)\n");
    else
        printf("Equacao Fundamental: NAO RESPEITADA!\n");
}

void calcularIndices(Balanco *balanco, DRE *dre, Resultado *res) {
    printf("\n--- INDICES FINANCEIROS ---\n");

    // Liquidez
    double liqCorrente = (balanco->caixa + balanco->bancos + balanco->aplicacoes + balanco->contasReceber + balanco->estoques)
                        / (balanco->fornecedores + balanco->contasPagar);
    double liqSeca = (balanco->caixa + balanco->bancos + balanco->aplicacoes + balanco->contasReceber)
                     / (balanco->fornecedores + balanco->contasPagar);
    printf("Liquidez Corrente:\t%.2f\n", liqCorrente);
    printf("Liquidez Seca:\t\t%.2f\n", liqSeca);

    // Giro Estoque
    double giroEstoque = dre->custoMercadorias / balanco->estoques;
    printf("Giro do Estoque:\t%.2f\n", giroEstoque);

    // Prazo Medio Recebimento
    double vendasAnuais = dre->receitaBruta;
    double prazoReceb = balanco->contasReceber / (vendasAnuais / 365);
    printf("Prazo Medio Recebimento:\t%.2f dias\n", prazoReceb);

    // Prazo Medio Pagamento
    double comprasAnuais = dre->custoMercadorias; // supondo 100% CMV
    double prazoPagamento = (balanco->fornecedores) / (comprasAnuais / 365);
    printf("Prazo Medio Pagamento:\t%.2f dias\n", prazoPagamento);

    // Giro do Ativo Total
    double totalAtivo = balanco->caixa + balanco->bancos + balanco->aplicacoes + balanco->contasReceber + balanco->estoques
                       + balanco->realizavelLP + balanco->investimentos + balanco->imobilizado + balanco->intangivel;
    double giroAtivo = vendasAnuais / totalAtivo;
    printf("Giro do Ativo Total:\t%.2f\n", giroAtivo);

    // Endividamento
    double totalPassivo = balanco->fornecedores + balanco->contasPagar + balanco->emprestimosLP + balanco->provisoes;
    double endividamento = totalPassivo / totalAtivo;
    printf("Endividamento Geral:\t%.2f\n", endividamento);

    // Rentabilidade
    printf("Margem Lucro Bruto:\t%.2f\n", res->lucroBruto / vendasAnuais);
    printf("Margem Lucro Operacional:\t%.2f\n", res->lucroOperacional / vendasAnuais);
    printf("Margem Lucro Liquido:\t%.2f\n", res->lucroLiquido / vendasAnuais);
}

int main() {
    DRE dre;
    Balanco balanco;
    Resultado res;

    printf("---- DRE ----\n");
    printf("Receita Bruta: ");
    scanf("%lf", &dre.receitaBruta);
    printf("Deducoes: ");
    scanf("%lf", &dre.deducoes);
    printf("Custo Mercadorias (CMV): ");
    scanf("%lf", &dre.custoMercadorias);
    printf("Despesas Operacionais: ");
    scanf("%lf", &dre.despesasOperacionais);
    printf("Despesas Financeiras: ");
    scanf("%lf", &dre.despesasFinanceiras);
    printf("Receitas Financeiras: ");
    scanf("%lf", &dre.receitasFinanceiras);
    printf("Imposto de Renda: ");
    scanf("%lf", &dre.impostoRenda);
    printf("CSL: ");
    scanf("%lf", &dre.csl);

    calcularDRE(&dre, &res);

    printf("\n---- BALANCO PATRIMONIAL ----\n");

    printf("Caixa: "); scanf("%lf", &balanco.caixa);
    printf("Bancos: "); scanf("%lf", &balanco.bancos);
    printf("Aplicacoes Financeiras: "); scanf("%lf", &balanco.aplicacoes);
    printf("Contas a Receber: "); scanf("%lf", &balanco.contasReceber);
    printf("Estoques: "); scanf("%lf", &balanco.estoques);

    printf("Realizavel a Longo Prazo: "); scanf("%lf", &balanco.realizavelLP);
    printf("Investimentos: "); scanf("%lf", &balanco.investimentos);
    printf("Imobilizado: "); scanf("%lf", &balanco.imobilizado);
    printf("Intangivel: "); scanf("%lf", &balanco.intangivel);

    printf("Fornecedores: "); scanf("%lf", &balanco.fornecedores);
    printf("Contas a Pagar: "); scanf("%lf", &balanco.contasPagar);
    printf("Emprestimos e Financiamentos: "); scanf("%lf", &balanco.emprestimosLP);
    printf("Provisoes: "); scanf("%lf", &balanco.provisoes);

    printf("Capital Social: "); scanf("%lf", &balanco.capitalSocial);
    printf("Reservas de Capital: "); scanf("%lf", &balanco.reservasCapital);
    printf("Reservas de Lucros: "); scanf("%lf", &balanco.reservasLucros);
    printf("Lucros Acumulados: "); scanf("%lf", &balanco.lucrosAcumulados);

    calcularBalanco(&balanco, &res);
    calcularIndices(&balanco, &dre, &res);

    return 0;
}
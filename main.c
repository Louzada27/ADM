#include <stdio.h>
#include <stdlib.h>

// -------- STRUCTS --------
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
    // Ativo Circulante
    double caixa, bancos, aplicacoes, contasReceber, estoques;

    // Ativo Não Circulante
    double realizavelLP, investimentos, imobilizado, intangivel;

    // Passivo
    double fornecedores, contasPagar;
    double emprestimosLP, provisoes;

    // PL
    double capitalSocial, reservasCapital, reservasLucros, lucrosAcumulados;
} Balanco;

typedef struct {
    double receitaLiquida;
    double lucroBruto;
    double lucroOperacional;
    double lucroAntesIR;
    double lucroLiquido;
} Resultado;

// -------- DRE --------
void calcularDRE(DRE *dre, Resultado *res) {

    res->receitaLiquida = dre->receitaBruta - dre->deducoes;
    res->lucroBruto = res->receitaLiquida - dre->custoMercadorias;
    res->lucroOperacional = res->lucroBruto - dre->despesasOperacionais;
    res->lucroAntesIR = res->lucroOperacional - dre->despesasFinanceiras + dre->receitasFinanceiras;
    res->lucroLiquido = res->lucroAntesIR - (dre->impostoRenda + dre->csl);

    printf("\n--- RELATORIO: DRE ---\n");
    printf("Receita Liquida:\t\t R$ %.2f\n", res->receitaLiquida);
    printf("Lucro Bruto:\t\t\t R$ %.2f\n", res->lucroBruto);
    printf("Lucro Operacional:\t\t R$ %.2f\n", res->lucroOperacional);
    printf("Lucro Antes IR:\t\t\t R$ %.2f\n", res->lucroAntesIR);
    printf("Lucro Liquido:\t\t\t R$ %.2f\n", res->lucroLiquido);
}

// -------- BALANÇO --------
void calcularBalanco(Balanco *b, double lucro) {

    b->lucrosAcumulados += lucro;

    double ac = b->caixa + b->bancos + b->aplicacoes + b->contasReceber + b->estoques;
    double anc = b->realizavelLP + b->investimentos + b->imobilizado + b->intangivel;
    double ativoTotal = ac + anc;

    double pc = b->fornecedores + b->contasPagar;
    double pnc = b->emprestimosLP + b->provisoes;
    double pl = b->capitalSocial + b->reservasCapital + b->reservasLucros + b->lucrosAcumulados;

    double total = pc + pnc + pl;

    printf("\n--- BALANCO PATRIMONIAL ---\n");

    printf("\nATIVO\n");
    printf("Circulante:\t\t R$ %.2f\n", ac);
    printf("Nao Circulante:\t\t R$ %.2f\n", anc);
    printf("TOTAL:\t\t\t R$ %.2f\n", ativoTotal);

    printf("\nPASSIVO\n");
    printf("Circulante:\t\t R$ %.2f\n", pc);
    printf("Nao Circulante:\t\t R$ %.2f\n", pnc);
    printf("TOTAL:\t\t\t R$ %.2f\n", pc + pnc);

    printf("\nPATRIMONIO LIQUIDO\n");
    printf("TOTAL:\t\t\t R$ %.2f\n", pl);

    printf("\nPASSIVO + PL:\t\t R$ %.2f\n", total);

    if (ativoTotal == total)
        printf("EQUAÇÃO FUNDAMENTAL: OK\n");
    else
        printf("EQUAÇÃO FUNDAMENTAL: ERRO\n");
}

// -------- INDICES --------
void calcularIndices(Balanco *b, DRE *d, Resultado *r) {

    double ac = b->caixa + b->bancos + b->aplicacoes + b->contasReceber + b->estoques;
    double pc = b->fornecedores + b->contasPagar;
    double ativoTotal = ac + b->realizavelLP + b->investimentos + b->imobilizado + b->intangivel;
    double passivoTotal = pc + b->emprestimosLP + b->provisoes;

    double compras = d->custoMercadorias * 0.7;

    printf("\n--- INDICES ---\n");

    printf("Liquidez Corrente:\t %.2f\n", ac / pc);
    printf("Liquidez Seca:\t\t %.2f\n", (ac - b->estoques) / pc);

    printf("Giro Estoque:\t\t %.2f\n", d->custoMercadorias / b->estoques);
    printf("PM Recebimento:\t\t %.2f dias\n", b->contasReceber / (d->receitaBruta / 365));
    printf("PM Pagamento:\t\t %.2f dias\n", b->fornecedores / (compras / 365));

    printf("Giro Ativo:\t\t %.2f\n", d->receitaBruta / ativoTotal);
    printf("Endividamento:\t\t %.2f\n", passivoTotal / ativoTotal);

    printf("Margem Bruta:\t\t %.2f%%\n", (r->lucroBruto / r->receitaLiquida) * 100);
    printf("Margem Operacional:\t %.2f%%\n", (r->lucroOperacional / r->receitaLiquida) * 100);
    printf("Margem Liquida:\t\t %.2f%%\n", (r->lucroLiquido / r->receitaLiquida) * 100);
}

// -------- MAIN --------
int main() {

    DRE d = {0};
    Balanco b = {0};
    Resultado r = {0};
    char nome[50];

    printf("Nome da Empresa: ");
    scanf(" %[^\n]", nome); // CORREÇÃO AQUI

    // -------- DRE --------
    printf("\n--- ENTRADA DRE ---\n");
    printf("Receita Bruta: "); scanf("%lf", &d.receitaBruta);
    printf("Deducoes: "); scanf("%lf", &d.deducoes);
    printf("CMV: "); scanf("%lf", &d.custoMercadorias);
    printf("Despesas Operacionais: "); scanf("%lf", &d.despesasOperacionais);
    printf("Despesas Financeiras: "); scanf("%lf", &d.despesasFinanceiras);
    printf("Receitas Financeiras: "); scanf("%lf", &d.receitasFinanceiras);
    printf("IR: "); scanf("%lf", &d.impostoRenda);
    printf("CSL: "); scanf("%lf", &d.csl);

    calcularDRE(&d, &r);

    // -------- ATIVO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (ATIVO CIRCULANTE) ---\n");
    printf("Caixa: "); scanf("%lf", &b.caixa);
    printf("Bancos: "); scanf("%lf", &b.bancos);
    printf("Aplicacoes: "); scanf("%lf", &b.aplicacoes);
    printf("Contas a Receber: "); scanf("%lf", &b.contasReceber);
    printf("Estoques: "); scanf("%lf", &b.estoques);

    // -------- ATIVO NÃO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (ATIVO NAO CIRCULANTE) ---\n");
    printf("Realizavel LP: "); scanf("%lf", &b.realizavelLP);
    printf("Investimentos: "); scanf("%lf", &b.investimentos);
    printf("Imobilizado: "); scanf("%lf", &b.imobilizado);
    printf("Intangivel: "); scanf("%lf", &b.intangivel);

    // -------- PASSIVO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (PASSIVO CIRCULANTE) ---\n");
    printf("Fornecedores: "); scanf("%lf", &b.fornecedores);
    printf("Contas a Pagar: "); scanf("%lf", &b.contasPagar);

    // -------- PASSIVO NÃO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (PASSIVO NAO CIRCULANTE) ---\n");
    printf("Emprestimos LP: "); scanf("%lf", &b.emprestimosLP);
    printf("Provisoes: "); scanf("%lf", &b.provisoes);

    // -------- PATRIMÔNIO LÍQUIDO --------
    printf("\n--- ENTRADA BALANCO (PATRIMONIO LIQUIDO) ---\n");
    printf("Capital Social: "); scanf("%lf", &b.capitalSocial);
    printf("Reservas de Capital: "); scanf("%lf", &b.reservasCapital);
    printf("Reservas de Lucros: "); scanf("%lf", &b.reservasLucros);
    printf("Lucros Acumulados (Inicial): "); scanf("%lf", &b.lucrosAcumulados);

    calcularBalanco(&b, r.lucroLiquido);
    calcularIndices(&b, &d, &r);

    return 0;
}

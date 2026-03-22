#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

    if (fabs(ativoTotal - total) < 0.01)
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
    int modoTeste;

    printf("Modo teste? (1=sim / 0=nao): ");
    scanf("%d", &modoTeste);

    DRE d = {0};
    Balanco b = {0};
    Resultado r = {0};
    char nome[50];

    
    if(modoTeste == 0){
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
    }else{
    printf("\nNome da Empresa: Teste LTDA\n");

    // -------- DRE --------
    printf("\n--- ENTRADA DRE ---\n");

    d.receitaBruta = 100000;
    printf("Receita Bruta: %.2f\n", d.receitaBruta);

    d.deducoes = 5000;
    printf("Deducoes: %.2f\n", d.deducoes);

    d.custoMercadorias = 40000;
    printf("CMV: %.2f\n", d.custoMercadorias);

    d.despesasOperacionais = 15000;
    printf("Despesas Operacionais: %.2f\n", d.despesasOperacionais);

    d.despesasFinanceiras = 2000;
    printf("Despesas Financeiras: %.2f\n", d.despesasFinanceiras);

    d.receitasFinanceiras = 1000;
    printf("Receitas Financeiras: %.2f\n", d.receitasFinanceiras);

    d.impostoRenda = 5000;
    printf("IR: %.2f\n", d.impostoRenda);

    d.csl = 2000;
    printf("CSL: %.2f\n", d.csl);

    calcularDRE(&d, &r);

    // -------- ATIVO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (ATIVO CIRCULANTE) ---\n");

    b.caixa = 20000;
    printf("Caixa: %.2f\n", b.caixa);

    b.bancos = 10000;
    printf("Bancos: %.2f\n", b.bancos);

    b.aplicacoes = 5000;
    printf("Aplicacoes: %.2f\n", b.aplicacoes);

    b.contasReceber = 15000;
    printf("Contas a Receber: %.2f\n", b.contasReceber);

    b.estoques = 10000;
    printf("Estoques: %.2f\n", b.estoques);

    // -------- ATIVO NÃO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (ATIVO NAO CIRCULANTE) ---\n");

    b.realizavelLP = 8000;
    printf("Realizavel LP: %.2f\n", b.realizavelLP);

    b.investimentos = 10000;
    printf("Investimentos: %.2f\n", b.investimentos);

    b.imobilizado = 20000;
    printf("Imobilizado: %.2f\n", b.imobilizado);

    b.intangivel = 10000;
    printf("Intangivel: %.2f\n", b.intangivel);

    // -------- PASSIVO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (PASSIVO CIRCULANTE) ---\n");

    b.fornecedores = 9000;
    printf("Fornecedores: %.2f\n", b.fornecedores);

    b.contasPagar = 4000;
    printf("Contas a Pagar: %.2f\n", b.contasPagar);

    // -------- PASSIVO NÃO CIRCULANTE --------
    printf("\n--- ENTRADA BALANCO (PASSIVO NAO CIRCULANTE) ---\n");

    b.emprestimosLP = 15000;
    printf("Emprestimos LP: %.2f\n", b.emprestimosLP);

    b.provisoes = 5000;
    printf("Provisoes: %.2f\n", b.provisoes);

    // -------- PATRIMÔNIO LÍQUIDO --------
    printf("\n--- ENTRADA BALANCO (PATRIMONIO LIQUIDO) ---\n");

    b.capitalSocial = 30000;
    printf("Capital Social: %.2f\n", b.capitalSocial);

    b.reservasCapital = 8000;
    printf("Reservas de Capital: %.2f\n", b.reservasCapital);

    b.reservasLucros = 3000;
    printf("Reservas de Lucros: %.2f\n", b.reservasLucros);

    b.lucrosAcumulados = 2000;
    printf("Lucros Acumulados (Inicial): %.2f\n", b.lucrosAcumulados);

    calcularBalanco(&b, r.lucroLiquido);
    calcularIndices(&b, &d, &r);
}
    return 0;
}

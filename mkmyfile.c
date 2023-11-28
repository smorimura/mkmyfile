/*
 * mkmyfile.c		by Shun Morimura
 *
 * 本ファイルは使用するシステムの標準的な文字コーディング方式と改行コードに変換してコンパイルすること。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libshun.h>

#define PROGRAM_NAME "mkmyfile"
#define VERSION "1.0.0"

#define USAGE "\
%s - 俊専用ベタ書きテキストファイルのひな形を作成する\n\
by Shun Morimura Version %s\n\
\n\
使い方：\n\
    %s [-h] [-v] filename\n\
\n\
  新規ファイルとしてfilenameを作成し，btxconvで処理可能なベタ書きテキストファイルとしてのヘッダ情報等を書き込む。\n\
\n\
"

#define PREAMBLE1  "%% language=Japanese\n"
#ifdef UTF_8
 #define PREAMBLE2 "%% encoding=UTF-8\n"
#endif
#ifdef Shift_JIS
 #define PREAMBLE2 "%% encoding=Shift_JIS\n"
#endif
#ifdef EUC_JP
 #define PREAMBLE2 "%% encoding=EUC-JP\n"
#endif
#ifdef LF
 #define PREAMBLE3 "%% end of line=LF\n"
#endif
#ifdef CR
 #define PREAMBLE3 "%% end of line=CR\n"
#endif
#ifdef CRLF
 #define PREAMBLE3 "%% end of line=CRLF\n"
#endif
#define PREAMBLE4  "%% 本テキストファイルはそのままでも読めるよう工夫されていますが，拙作btxconvを用いることで，HTMLやLaTeXなどのさまざまなフォーマットに変換することができ，より美しい表示結果が得られます。\n\
\n\
タイトル：？？？\n\
サブタイトル：？？？\n\
著者：森村 俊\n\
日付：？年？月？日\n\
目次：作成|なし\n\
\n\
■ここから\n\
"

const char *PREAMBLE = PREAMBLE1 PREAMBLE2 PREAMBLE3 PREAMBLE4;

static void Version(void)
{
	printf(PROGRAM_NAME " by Shun Morimura Version " VERSION "\n");

	exit(EXIT_SUCCESS);
}

static void Usage(void)
{
	printf(USAGE, PROGRAM_NAME, VERSION, PROGRAM_NAME);

	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	int i;
	char com_opt_arg[COM_OPT_ARG_SIZE];
	char filename[COM_OPT_ARG_SIZE + 1];
	SH_bool is_filename = FALSE;
	FILE *fp;

	for (i = 1; i < argc; ++i) {
		switch (SH_GetComParameter(argv[i], com_opt_arg, "")) {
		case 'v':
			Version();
			break;
		case 'h':
			Usage();
			break;
		case '\0':	/* filename specified */
			if (strlen(argv[i]) >= COM_OPT_ARG_SIZE) {
				SH_ErrorExit("too long filename\n");
			}
			is_filename = TRUE;
			strncpy(filename, argv[i], COM_OPT_ARG_SIZE);
			break;
		default:
			SH_ErrorExit("unknown option '-%c'\n", argv[i][1]);
			break;
		}
	}

	if (is_filename == FALSE) {
		Usage();
		return(EXIT_SUCCESS);
	}

	if ((fp = fopen(filename, "r")) != NULL) {
		SH_ErrorExit("file '%s' already exists\n", filename);
	}

	if ((fp = fopen(filename, "w")) == NULL) {
		SH_ErrorExit("can't create '%s'\n", filename);
	}

	if (fputs(PREAMBLE, fp) == EOF) {
		SH_ErrorExit("can't write correctly to '%s'\n", filename);
	}

	if (fclose(fp) == EOF) {
		SH_ErrorExit("can't close '%s%u'\n", filename);
	}

	puts("done.");

	return(EXIT_SUCCESS);
}



#ifndef SOUNDKONVERTER_CODEC_MAC_H
#define SOUNDKONVERTER_CODEC_MAC_H

#include "../../core/codecplugin.h"

class ConversionOptions;


class soundkonverter_codec_mac : public CodecPlugin
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundkonverter_codec_mac( QObject *parent, const QStringList& args );

    /** Default Destructor */
    virtual ~soundkonverter_codec_mac();

    QString name();

    QList<ConversionPipeTrunk> codecTable();

    bool isConfigSupported( ActionType action, const QString& codecName );
    void showConfigDialog( ActionType action, const QString& codecName, QWidget *parent );
    bool hasInfo();
    void showInfo( QWidget *parent );

    CodecWidget *newCodecWidget();

    unsigned int convert( const KUrl& inputFile, const KUrl& outputFile, const QString& inputCodec, const QString& outputCodec, ConversionOptions *_conversionOptions, TagData *tags = 0, bool replayGain = false );
    QStringList convertCommand( const KUrl& inputFile, const KUrl& outputFile, const QString& inputCodec, const QString& outputCodec, ConversionOptions *_conversionOptions, TagData *tags = 0, bool replayGain = false );
    float parseOutput( const QString& output );

    ConversionOptions *conversionOptionsFromXml( QDomElement conversionOptions, QList<QDomElement> *filterOptionsElements = 0 )
    {
        return CodecPlugin::conversionOptionsFromXmlDefault( conversionOptions, filterOptionsElements );
    }
};

K_EXPORT_SOUNDKONVERTER_CODEC( mac, soundkonverter_codec_mac )


#endif // _SOUNDKONVERTER_CODEC_MAC_H_



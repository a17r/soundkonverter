
#include "lamecodecglobal.h"

#include "soundkonverter_codec_lame.h"
#include "lameconversionoptions.h"
#include "lamecodecwidget.h"


#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>
#include <KLocale>
#include <KComboBox>
#include <KDialog>
#include <QSpinBox>
#include <QGroupBox>
#include <QSlider>

soundkonverter_codec_lame::soundkonverter_codec_lame( QObject *parent, const QStringList& args  )
    : CodecPlugin( parent )
{
    binaries["lame"] = "";
    
    allCodecs += "mp3";
    allCodecs += "mp2";
    allCodecs += "wav";
}

soundkonverter_codec_lame::~soundkonverter_codec_lame()
{}

QString soundkonverter_codec_lame::name()
{
    return global_plugin_name;
}

QList<ConversionPipeTrunk> soundkonverter_codec_lame::codecTable()
{
    QList<ConversionPipeTrunk> table;
    ConversionPipeTrunk newTrunk;

    newTrunk.codecFrom = "wav";
    newTrunk.codecTo = "mp3";
    newTrunk.rating = 100;
    newTrunk.enabled = ( binaries["lame"] != "" );
    newTrunk.problemInfo = i18n("In order to encode mp3 files, you need to install 'lame'.\nSince mp3 is a patented file format, lame may not be included in the default installation of your distribution.\nMany distributions offer lame in an additional software repository.");
    newTrunk.data.hasInternalReplayGain = true;
    table.append( newTrunk );

    newTrunk.codecFrom = "mp3";
    newTrunk.codecTo = "wav";
    newTrunk.rating = 100;
    newTrunk.enabled = ( binaries["lame"] != "" );
    newTrunk.problemInfo = i18n("In order to decode mp3 files, you need to install 'lame'.\nSince mp3 is a patented file format, lame may not be included in the default installation of your distribution.\nMany distributions offer lame in an additional software repository.");
    newTrunk.data.hasInternalReplayGain = false;
    table.append( newTrunk );

    newTrunk.codecFrom = "mp3";
    newTrunk.codecTo = "mp3";
    newTrunk.rating = 100;
    newTrunk.enabled = ( binaries["lame"] != "" );
    newTrunk.problemInfo = i18n("In order to encode/decode mp3 files, you need to install 'lame'.\nSince mp3 is a patented file format, lame may not be included in the default installation of your distribution.\nMany distributions offer lame in an additional software repository.");
    newTrunk.data.hasInternalReplayGain = true;
    table.append( newTrunk );

    newTrunk.codecFrom = "mp2";
    newTrunk.codecTo = "wav";
    newTrunk.rating = 70;
    newTrunk.enabled = ( binaries["lame"] != "" );
    newTrunk.problemInfo = i18n("In order to decode mp2 files, you need to install 'lame'.\nSince mp3 is a patented file format, lame may not be included in the default installation of your distribution.\nMany distributions offer lame in an additional software repository.");
    newTrunk.data.hasInternalReplayGain = false;
    table.append( newTrunk );

    newTrunk.codecFrom = "mp2";
    newTrunk.codecTo = "mp3";
    newTrunk.rating = 70;
    newTrunk.enabled = ( binaries["lame"] != "" );
    newTrunk.problemInfo = i18n("In order to encode mp3/decode mp2 files, you need to install 'lame'.\nSince mp3 is a patented file format, lame may not be included in the default installation of your distribution.\nMany distributions offer lame in an additional software repository.");
    newTrunk.data.hasInternalReplayGain = true;
    table.append( newTrunk );

    return table;
}

BackendPlugin::FormatInfo soundkonverter_codec_lame::formatInfo( const QString& codecName )
{
    BackendPlugin::FormatInfo info;
    info.codecName = codecName;

    if( codecName == "mp3" )
    {
        info.lossless = false;
        info.description = i18n("MP3 is a very popular lossy audio codec.");
        info.mimeTypes.append( "audio/x-mp3" );
        info.mimeTypes.append( "audio/mpeg" );
        info.extensions.append( "mp3" );
    }
    else if( codecName == "mp2" )
    {
        info.lossless = false;
        info.description = i18n("MP2 is an old lossy audio codec.");
        info.mimeTypes.append( "audio/x-mp2" );
        info.extensions.append( "mp2" );
    }
    else if( codecName == "wav" )
    {
        info.lossless = true;
        info.description = i18n("Wave won't compress the audio stream.");
        info.mimeTypes.append( "audio/x-wav" );
        info.mimeTypes.append( "audio/wav" );
        info.extensions.append( "wav" );
    }

    return info;
}

// QString soundkonverter_codec_lame::getCodecFromFile( const KUrl& filename, const QString& mimeType )
// {
//     if( mimeType == "audio/x-mp3" || mimeType == "audio/mp3" || mimeType == "audio/mpeg" )
//     {
//         return "mp3";
//     }
//     else if( mimeType == "audio/x-mp2" || mimeType == "audio/mp2" || mimeType == "video/mpeg" )
//     {
//         return "mp2";
//     }
//     else if( mimeType == "audio/x-wav" || mimeType == "audio/wav" )
//     {
//         return "wav";
//     }
//     else if( mimeType == "application/octet-stream" )
//     {
//         if( filename.url().endsWith(".mp3") ) return "mp3";
//         if( filename.url().endsWith(".mp2") ) return "mp2";
//         if( filename.url().endsWith(".wav") ) return "wav";
//     }
// 
//     return "";
// }

bool soundkonverter_codec_lame::isConfigSupported( ActionType action, const QString& codecName )
{
    return true;
}

void soundkonverter_codec_lame::showConfigDialog( ActionType action, const QString& codecName, QWidget *parent )
{
    KDialog *dialog = new KDialog( parent );
    dialog->setCaption( i18n("Configure %1").arg(global_plugin_name)  );
    dialog->setButtons( KDialog::Ok | KDialog::Cancel | KDialog::Apply );

    QWidget *widget = new QWidget( dialog );
    

    dialog->setMainWidget( widget );
//     connect( dialog, SIGNAL( applyClicked() ), widget, SLOT( save() ) );
//     connect( dialog, SIGNAL( okClicked() ), widget, SLOT( save() ) );
//     connect( widget, SIGNAL( changed( bool ) ), dialog, SLOT( enableButtonApply( bool ) ) );

    dialog->enableButtonApply( false );
    dialog->show();
}

bool soundkonverter_codec_lame::hasInfo()
{
    return true;
}

void soundkonverter_codec_lame::showInfo( QWidget *parent )
{
    KDialog *dialog = new KDialog( parent );
    dialog->setCaption( i18n("About %1").arg(global_plugin_name)  );
    dialog->setButtons( KDialog::Ok );

    QLabel *widget = new QLabel( dialog );
    
    widget->setText( i18n("LAME is a free high quality MP3 encoder.\nYou can get it at: http://lame.sourceforge.net") );

    dialog->setMainWidget( widget );

    dialog->enableButtonApply( false );
    dialog->show();
}

QWidget *soundkonverter_codec_lame::newCodecWidget()
{
    LameCodecWidget *widget = new LameCodecWidget();
    if( lastUsedConversionOptions )
    {
        widget->setCurrentConversionOptions( lastUsedConversionOptions );
        delete lastUsedConversionOptions;
        lastUsedConversionOptions = 0;
    }
    return qobject_cast<QWidget*>(widget);
}

int soundkonverter_codec_lame::convert( const KUrl& inputFile, const KUrl& outputFile, const QString& inputCodec, const QString& outputCodec, ConversionOptions *_conversionOptions, TagData *tags, bool replayGain )
{
    QStringList command = convertCommand( inputFile, outputFile, inputCodec, outputCodec, _conversionOptions, tags, replayGain );
    if( command.isEmpty() ) return -1;

    CodecPluginItem *newItem = new CodecPluginItem( this );
    newItem->id = lastId++;
    newItem->process = new KProcess( newItem );
    newItem->process->setOutputChannelMode( KProcess::MergedChannels );
    connect( newItem->process, SIGNAL(readyRead()), this, SLOT(processOutput()) );
    connect( newItem->process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExit(int,QProcess::ExitStatus)) );

    newItem->process->clearProgram();
    newItem->process->setShellCommand( command.join(" ") );
    newItem->process->start();

    emit log( newItem->id, command.join(" ") );

    backendItems.append( newItem );
    return newItem->id;
}

QStringList soundkonverter_codec_lame::convertCommand( const KUrl& inputFile, const KUrl& outputFile, const QString& inputCodec, const QString& outputCodec, ConversionOptions *_conversionOptions, TagData *tags, bool replayGain )
{
    if( !_conversionOptions ) return QStringList();
    
    QStringList command;
    ConversionOptions *conversionOptions = _conversionOptions;
    LameConversionOptions *lameConversionOptions = 0;
    if( conversionOptions->pluginName == name() )
    {
        lameConversionOptions = static_cast<LameConversionOptions*>(conversionOptions);
    }

    if( outputCodec == "mp3" )
    {
        command += binaries["lame"];
        command += "--nohist";
        command += "--pad-id3v2";
        if( lameConversionOptions && lameConversionOptions->data.preset != LameConversionOptions::Data::UserDefined )
        {
            command += "--preset";
            if( lameConversionOptions->data.presetFast )
            {
                command += "fast";
            }
            if( lameConversionOptions->data.preset == LameConversionOptions::Data::Medium )
            {
                command += "medium";
            }
            else if( lameConversionOptions->data.preset == LameConversionOptions::Data::Standard )
            {
                command += "standard";
            }
            else if( lameConversionOptions->data.preset == LameConversionOptions::Data::Extreme )
            {
                command += "extreme";
            }
            else if( lameConversionOptions->data.preset == LameConversionOptions::Data::Insane )
            {
                command += "insane";
            }
            else if( lameConversionOptions->data.preset == LameConversionOptions::Data::SpecifyBitrate )
            {
                if( lameConversionOptions->data.presetBitrateCbr )
                {
                    command += "cbr";
                }
                command += QString::number(lameConversionOptions->data.presetBitrate);
            }
        }
        else
        {
            if( conversionOptions->qualityMode == ConversionOptions::Quality )
            {
                command += "--vbr-new";
                command += "-V";
                command += QString::number(conversionOptions->quality);
            }
            else if( conversionOptions->qualityMode == ConversionOptions::Bitrate )
            {
                if( conversionOptions->bitrateMode == ConversionOptions::Abr )
                {
                    command += "-abr";
                    command += QString::number(conversionOptions->bitrate);
                    if( conversionOptions->bitrateMin > 0 || conversionOptions->bitrateMax > 0 )
                    {
                        if( conversionOptions->bitrateMin > 0 )
                        {
                            command += "-b";
                            command += QString::number(conversionOptions->bitrateMin);
                        }
                        if( conversionOptions->bitrateMax > 0 )
                        {
                            command += "-B";
                            command += QString::number(conversionOptions->bitrateMax);
                        }
                    }
                }
                else if( conversionOptions->bitrateMode == ConversionOptions::Cbr )
                {
                    command += "-cbr";
                    command += "-b";
                    command += QString::number(conversionOptions->bitrate);
                }
            }
            if( conversionOptions->samplingRate > 0 )
            {
                command += "--resample";
                command += QString::number((float)conversionOptions->samplingRate/1000.0f);
            }
            if( conversionOptions->channels > 0 )
            {
                command += "-m";
                if( conversionOptions->channels == 1 )
                {
                    command += "m";
                }
                else if( conversionOptions->channels == 2 )
                {
                    command += "j";
                }
                else if( conversionOptions->channels == 3 )
                {
                    command += "s";
                }
                else if( conversionOptions->channels == 4 )
                {
                    command += "f";
                }
                else if( conversionOptions->channels == 5 )
                {
                    command += "d";
                }
            }
        }
        if( conversionOptions->pluginName == name() )
        {
            command += conversionOptions->cmdArguments;
        }
        command += "\"" + inputFile.toLocalFile() + "\"";
        command += "\"" + outputFile.toLocalFile() + "\"";
    }
    else
    {
        command += binaries["lame"];
        command += "--decode";
        command += "\"" + inputFile.toLocalFile() + "\"";
        command += "\"" + outputFile.toLocalFile() + "\"";
    }

    return command;
}

float soundkonverter_codec_lame::parseOutput( const QString& output )
{
    // decoding
    // Frame#  1398/8202   256 kbps  L  R (...)
    
    // encoding
    // \r  3600/3696   (97%)|    0:05/    0:05|    0:05/    0:05|   18.190x|    0:00 
  
    QString data = output;
    QString frame, count;
    
    if( output.contains("Frame#") )
    {
        data.remove( 0, data.indexOf("Frame#")+7 );
        frame = data.left( data.indexOf("/") );
        data.remove( 0, data.indexOf("/")+1 );
        count = data.left( data.indexOf(" ") );
        return frame.toFloat()/count.toFloat()*100.0f;
    }
    if( output.contains("%") )
    {
        frame = data.left( data.indexOf("/") );
        frame.remove( 0, frame.lastIndexOf(" ")+1 );
        data.remove( 0, data.indexOf("/")+1 );
        count = data.left( data.indexOf(" ") );
        return frame.toFloat()/count.toFloat()*100.0f;
    }
    /*if( output.contains("%") )
    {
        data.remove( 0, data.indexOf("(")+1 );
        data.remove( data.indexOf("%"), data.length()-data.indexOf("%") );
        return data.toFloat();
    }*/
    
    return -1;
}

ConversionOptions *soundkonverter_codec_lame::conversionOptionsFromXml( QDomElement conversionOptions )
{
    LameConversionOptions *options = new LameConversionOptions();
    options->fromXml( conversionOptions );
    return options;
}


#include "soundkonverter_codec_lame.moc"

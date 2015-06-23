/*
  Copyright (c) 2012 Vinícius dos Santos Oliveira

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */

#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <QtCore/QObject>
#include <QProcess>
#include <Tufao/AbstractHttpServerRequestHandler>


class MainHandler : public QObject,
                    public Tufao::AbstractHttpServerRequestHandler
{
    Q_OBJECT
public:
    explicit MainHandler(QObject *parent = 0);
    void setThermalEnabled(bool enabled = true)
    {
        m_hasThermal = enabled;
    }

    bool getThermalEnabled() const
    {
        return m_hasThermal;
    }

public slots:
    bool handleRequest(Tufao::HttpServerRequest &request,
                       Tufao::HttpServerResponse &response) override;

private slots:
    void thermalProcessFinished();
    void piCamProcessFinished();

private:
    void printUsage(Tufao::HttpServerRequest &request,
                    Tufao::HttpServerResponse &response);

    void picameraHandler(Tufao::HttpServerRequest &request,
                         Tufao::HttpServerResponse &response);

    void thermalHandler(Tufao::HttpServerRequest &request,
                        Tufao::HttpServerResponse &response);

    void shutdownHandler(Tufao::HttpServerRequest &request,
                         Tufao::HttpServerResponse &response);

    bool m_hasThermal;
    QProcess *m_thermalProcess, *m_picamProcess;

};

#endif // MAINHANDLER_H

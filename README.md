Islandora Drupal Solr DataImportHandler Notifier

## Introduction

Causes selected Solr DataImportHandler to perform a 'delta-import' when node content is created or updated.

## Requirements

This module requires the following modules/libraries:

* [Islandora Solr](https://github.com/islandora/islandora_solr_search)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Enable the relevant DataImportHandlers as necessary as `admin/islandora/search/islandora_solr/drupal_notifier`.

For an additional ensurance of index consistency, it may be desirable to add a cron job to regularly make the DataImportHandler poll Drupal. Drupal uses DB transactions when saving node content, so we have to somehow make trigger to Solr after the DB is actually updated. Additionally, if an import is already in progress, it is not clearly specified what will happen; assuming the command will be ignore, it is recommended to add a cron job like the following to ensure eventual consistency:
```bash
# Make Solr's DataImportHandler poll Drupal for updated content every 5 minutes.
*/5 * * * * /usr/bin/wget "http://localhost:8080/solr/dataimport?command=full-import&clean=false"
```

## Troubleshooting/Issues

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

## Maintainers/Sponsors

Current maintainers:

* [discoverygarden Inc.](https://github.com/discoverygarden)


## Development

If you would like to contribute to this module, please check out our helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the Islandora.ca site.

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
